# Setup

Install `libboost`, `autoconf`, and `pkg-config`.

Build project using `make release` or `make debug`.

Build the custom NVML (old PMDK) using `make nvml`.

To build the examples, finally do `make nvml-example`.

# Examples

There are 5 examples built in, according to PMTest's docs:

* ctree
* btree
* rbtree
* hashmap_tx
* hashmap_atomic

You can run these using the following command, replacing `<example-name>` with the preferred example:

```
$ make nvml-exec arg=<example-name>
```

PMTest also provides some patches that introduce errors into these examples. See the last section of `README-old.md` for details.

# TODO

* The existing code doesn't have access to new values, only old values (value before write). We need to update it to also capture the new values at writes.
  See `PM_EQU`, `PMTest_assign`, `C_createMetadata_Assign`, and `VeriProc_Assign`.