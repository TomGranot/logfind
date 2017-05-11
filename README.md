# logfind
My version of [Zed Shaw's programming challenge](https://learncodethehardway.org/c/).

# How it works
`logfind` is a command-line utility designed to find strings inside any type of file. It uses the standard libray alone without any custom header files or OS-specific bits. It's longer than it should be, for sure, and if you have suggestions feel free to make a PR.

# Usage
`logfind` is basically `grep` without any of the really nice features, except for a simple "-o" flag (for *logical OR*).

So:

`./logfind tom jack phil` will find all the files that contain "tom" **AND** "jack" **AND** "phil" inside a specially designated folder in your user's root folder called `.logfind`.

`./logfind -o tom jack phil` will find all the files that contain "tom" **OR** "jack" **OR** "phil" inside `.logfind`.

If it finds a file that matches the logic, it prints out the file's name once - even if the string appears more than once inside said file.

# The .logfind folder

I've added a few files for you to play with - just copy the folder to your user's root and run the program from anywhere on your computer (tilde exapnsions for finding the root is used):

1. `yes.c` contains my name (tom) twice, on the same line.
2. `middle.c` contains my name in "atom" and "tom" form, as wel as "jack" in the middle of the file.
3. `no.c` does not contain "tom", "jack" nor "phil".

# Notes

1. `logfind` uses `strstr()`, so if you'll add the string "atom" to a file, for example, and then `logfind` my name -  you will get a match.
2. `logfind` plays nice with whitespaces and newlines - try it our by messing with the files inside the `.logfind` folder.
3. In the original exercise, .logfind is suppose to be a file - [like the one here](https://github.com/zedshaw/learn-c-the-hard-way-lectures/blob/master/ex26/logfind.4/.logfind) - with possible extensions to allow. My version does not support that - it searches through all possible files.
3. If you haven't seen Zed talk yet, you should - [link here](https://vimeo.com/53494258).
