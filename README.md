# Dezashibi Common library `dcommon`

This library is my personal utilities, types, helpers and macros that I often use in my projects.

The key concept in this library is **NOT** to be one lib rule them all style or full of complicated highly abstracted macros.

So you still need to know what you're writing and it might fail or causes undefined behavior.

Which comes with this question that should you use it or not!?

The answer is **I really don't care!**, just kidding 😄. You can use it because it's really clean and straight forward whether you want to hack it or learn from it, so if you want to have things already done and ready to be used and also easy to debug sure use it, if you're seeking something magical or you recently fell in love with `C` with some background on other languages it **does** provide a few features like dynamic values, dynamic arrays, hash tables, `result` type, etc. but in no way it's not going to remove the need for being actively focused on where you've allocated memory, when to free, etc.

**👉 By the way, you might have this idea that this library is sort of opinionated, well it is and I'll take that as a compliment 😊🤝.**

So if you're ready to give it a try by all means please go ahead and use this and I can't wait for your opinions.

**👉 NOTE:** The library is stable enough to be used, but I might want to add/remove a few macros and also improve documentation or I might add a quick start guide, that sort of things. that being said, don't trust me, use it in a smaller scale first, see if you can connect with it, let me know what you think.

## How the library is structured?

It's a one header file include style (**Not to be mistaken with single header libraries**):

- Download a release of `dcommon.zip`
- Unzip it to your `extern` or `src` folder and you'll have a `dcommon` folder in there
- Include `dcommon/dcommon.h` where ever you want to use it.
- Make sure you've added `DCOMMON_IMPL` before one and only one of your files before including the header file.
- That's it.

## What's on the menu?

- `dcommon` lib
  - Primitive type short names,
  - Inclusion of mostly used standard library header files
  - Dynamic value you can use and enjoy
  - Dynamic array can hold dynamic values
  - Hash Table with custom hash functions and key type
  - String View
  - Result type with macros to define your own, with returns success or error with error messages, codes, so on.
  - Everything returns result no number coding
  - string converter to numbers with proper bound check and errors
  - Global cleanup that you can register your types and make sure if anything is broken it will first cleanup then exit
  - Macros to log, condition based log, debug logs, etc.
  - Utilities to create formatted string, duplicate string, append string, etc.
  - ...
- `tag.py` Script
  - Simplifies creating tag, zip artifact or file attachment for github

**👉 `dcommon` lib help can be found [here](/src/dcommon/docs.md).**

## `tag.py` Script

The idea is to run this simple script after a few modification to create
tag and also release in case certain criteria are met
The script looks for `CHANGE_LOGS.md` in the current working directory
it assumes the mentioned file has the following format

👉 Checkout [`CHANGE_LOG.md`](/CHANGE_LOGS.md) of this very repository.

**👉 For `tag.py` guide read [here](/src/scripts/tag.py#L39-L70).**

This library uses `tag.py` like [this](/scripts/tag.py#L72-L80).

```py
# name of the folder to zip this path is relative to the current working directory
# it means if you run it from the root folder it looks for the folder to be zipped
# in the root folder
# leave it empty string `''` for disabling zip
folder_to_zip = ['src/dcommon']

# you can list name of file or files you would like to be added individually to github
# releases
release_files = ["src/dcommon.zip", "src/scripts/tag.py"]
```

And every time I need I just run the following command at the root of my repository folder:

```bash
python3 ./scripts/tag.py
```

## License

This project is licensed under the BSD 3-Clause [LICENSE](/LICENSE).

BSD 3-Clause License

Copyright (c) 2024, Navid Dezashibi <navid@dezashibi.com>

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its
   contributors may be used to endorse or promote products derived from
   this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
