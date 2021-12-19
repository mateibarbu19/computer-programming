# Homework 3 - Tar Archiver

Disclaimer: Because this is a old project, I left some variable names in
Romanian.

Table of Contents
=================

* [Homework 3 - Tar Archiver](#homework-3---tar-archiver)
   * [Task 0](#task-0)
   * [Task 1](#task-1)
   * [Task 2](#task-2)
   * [Task 3](#task-3)
   * [Usage](#usage)

Created by [gh-md-toc](https://github.com/ekalinin/github-markdown-toc)

## Task 0

> Description: Implement a command interpreter.

The shell is implemented in the main.c file. If I were to do it again for a more
professional project I would use a tool similar to GNU's getopt.

## Task 1

> Description: Implement the creation functionality

The `create()` function traverses each line in the files.txt file and, depending
on each field, completes the header corresponding to each file.

The contents of the files are copied to the .tar archive using the
`add_file_to_tar()` function. An empty register is added at the end.

## Task 2

> Description: Implement the display functionality.

The `list()` function also reads the header of each file in the archive and
displays its name. Then in the size field, it converts the number from octal to
decimal and skips how many registers the contents of the file represent.

## Task 3

> Description: Implement the extraction functionality.

The `extract()` function is similar to the list, but does not display the file
names in the archive. It copies the contents of the file to the archive file.

## Usage

```bash
user@user-pc:~$ ./archiver
create archive.tar
> Wrong command!
create archive.tar test_4/
> Done!
list archive.tar
> image1.png
> image2.png
> image3.png
exit
user@user-pc:~$
```


In the case of creating a `.tar` archive form a folder make sure to run these
precursory commands in it.

```bash
ls -la --time-style=full-iso $@ | grep '^-' | grep -Fv -e 'files.txt' -e 'usermap.txt' > files.txt
cat /etc/passwd > usermap.txt
```

This limitation is cause by the restriction to not use system calls.
