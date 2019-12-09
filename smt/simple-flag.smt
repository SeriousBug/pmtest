;; This example shows a simple case where the availability of a value x is
;; signalled using a flag f.
;;
;; Run this using `z3 simple-flag.smt`

;; Value
(declare-fun x (Int) Int)
;; Flag
(declare-fun f (Int) Int)
;; Position in execution
(declare-const pos Int)

;; The code works by splitting the execution into regions seperated by SFENCE
;; instructions. The regions are numbered 0 to N, and `pos` indicated which
;; region we are in.

;; The safety check we want to ask: Is there any position in the execution
;; where x is 0 (unset), but the flag is 1 (set)?
(assert (and (= (x pos) 0) (= (f pos) 1)))

;; The correct implementation
(push)
  ;; x = 0           |
  ;; f = 0           | region 0
  ;; CLWB, SFENCE;
  ;; x = 123;        | region 1
  ;; CLWB, SFENCE;
  ;; f = 1;          | region 2
  (assert (or
    ;; The flag changes from 0 to 1 in region 2
    (and (<= pos 2) (= (f pos) 0))
    (and (>= pos 2) (= (f pos) 1))
  ))
  (assert (or
    ;; x changes from 0 to 123 in rehion 1
    (and (<= pos 1) (= (x pos) 0))
    (and (>= pos 1) (= (x pos) 123))
  ))
  ;; Check if this is possible, give an example if it is.
  (check-sat)
  (get-model)
(pop)

;; The incorrect implementation
(push)
  ;; x = 0           |
  ;; f = 0           | region 0
  ;; CLWB, SFENCE;
  ;; x = 123;        | 
  ;; f = 1;          | region 1
  (assert (or
    ;; The flag changes from 0 to 1 in region 1
    (and (<= pos 1) (= (f pos) 0))
    (and (>= pos 1) (= (f pos) 1))
  ))
  (assert (or
    ;; x changes from 0 to 1 in region 1
    (and (<= pos 1) (= (x pos) 0))
    (and (>= pos 1) (= (x pos) 123))
  ))
  ;; Check if this is possible, give an example if it is.
  (check-sat)
  (get-model)
(pop)
(exit)