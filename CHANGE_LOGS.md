## v0.9.5-beta

Release Date: 2024-10-25

- add boolean type as b1
- add both union extra fields and regular struct extra fields for dynamic value
- improve primitive types
- add dynamic array and hash table pointer to dynamic value with proper free and printing
- add new macros
- change DCKeyValue to DCPair
- simplify names

=======

## v0.9.2-beta

Release Date: 2024-10-17

- add break out of loop feature with macro
- improve hash table free process
- fix string view bug on boundary check
- move result type to primitives

=======

## v0.9.0-beta

Release Date: 2024-10-15

- add string view to dynamic value as well
- add status for hash table set and merge (can only be updated, created or both)
- remove many redundant macros
- improve namings
- format specifier for each primitive type
- separate primitive types from the main header file (check [test_dv_da_extra_fields.c](/examples/test_dv_da_extra_fields.c))
- add more macros
- shorten names
- dynamic value is now supporting any number of extra fields in its union
- new example is added (check [test_dv_da_extra_fields.c](/examples/test_dv_da_extra_fields.c))
- change hash table key to dynamic value
- update all tests and examples

=======

## v0.8.1-beta

Release Date: 2024-09-27

- Fix macro errors
- Add more logging macros

=======

## v0.8.0-beta

Release Date: 2024-09-26

- adding documentations
- Simplify exit label process
- Simplify cleanup processes
- Add time stamp for logging
- Testing logs to file
- re-test everything
- all memory management parts work as expected
- add result type
- rewrite everything to support result type
- add string converters to literal numbers
- simplify global cleanup procedure
- add allocated field to dynamic values
- add string append func
- add mem cleanup on exit global
- add deferred mem cleanup local
- add debug macros
- add hash map
- add utils
- path utils
- colorization
- get user basic data
- string utils
- add string view
- simplify all the for loops
- add conversion of dynamic array to flat array of same types
- literal arrays
- dynamic arrays
- for each
- on each
- struct arrays
- Working examples

=======

## v0.0.1

Date: 2024-09-08

- initialize the repo
