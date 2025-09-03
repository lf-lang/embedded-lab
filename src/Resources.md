# Resources

This page provides resources and references for working with Unix command line tools and embedded development.

## Unix Command Line Basics

### Essential Commands

- **`ls`** - List directory contents
  - `ls -a` - Show all files (including hidden ones)
  - `ls -l` - Long format listing
  - `ls -h` - Human-readable file sizes
  - `ls -la` - Combine flags for detailed listing with hidden files

- **`cd`** - Change directory
  - `cd ..` - Move to parent directory
  - `cd ~` - Move to home directory
  - `cd -` - Move to previous directory

- **`pwd`** - Print working directory (shows current location)

- **`cp`** - Copy files and directories
  - `cp source destination` - Copy file
  - `cp -r source destination` - Copy directory recursively

- **`mv`** - Move/rename files and directories
  - `mv oldname newname` - Rename file
  - `mv file directory/` - Move file to directory

- **`rm`** - Remove files and directories
  - `rm file` - Remove file
  - `rm -r directory` - Remove directory recursively
  - `rm -f file` - Force remove (no confirmation)

- **`mkdir`** - Create directory
  - `mkdir -p path/to/dir` - Create parent directories if needed

- **`man`** - Display manual pages
  - `man command` - Show manual for command
  - `man -k keyword` - Search manual pages

### File Navigation and Viewing

- **`cat`** - Concatenate and display file contents
- **`less`** - View file contents with pagination
- **`head`** - Display first lines of file
- **`tail`** - Display last lines of file
- **`grep`** - Search for patterns in files
  - `grep "pattern" file` - Search for pattern in file
  - `grep -r "pattern" directory` - Search recursively

### Process Management

- **`ps`** - Show running processes
- **`top`** - Interactive process viewer
- **`kill`** - Terminate processes
- **`jobs`** - List background jobs
- **`fg`** - Bring job to foreground
- **`bg`** - Send job to background

### Network and System

- **`ping`** - Test network connectivity
- **`ssh`** - Secure shell connection
- **`scp`** - Secure copy over SSH
- **`wget`** - Download files from web
- **`curl`** - Transfer data from/to servers

## Git Basics

- **`git status`** - Show repository status and changes
- **`git add`** - Stage changes for commit
- **`git commit`** - Commit staged changes
- **`git push`** - Push commits to remote repository
- **`git pull`** - Pull changes from remote repository
- **`git clone`** - Clone repository from remote
- **`git branch`** - List/create/delete branches
- **`git checkout`** - Switch branches or restore files
- **`git log`** - Show commit history

## Text Editors

### Command Line Editors

- **`nano`** - Simple, beginner-friendly editor
- **`vim`** - Powerful modal editor
- **`emacs`** - Extensible editor

### VS Code

- **`code .`** - Open current directory in VS Code
- **`code file`** - Open specific file in VS Code

## Useful Shell Features

### Tab Completion
Press Tab to auto-complete file names, commands, and paths.

### Command History
- **`history`** - Show command history
- **`!n`** - Execute command number n from history
- **`!!`** - Execute last command
- **`!$`** - Use last argument of previous command

### Aliases
Create shortcuts for commonly used commands:
```bash
alias ll='ls -la'
alias ..='cd ..'
```

### Environment Variables
- **`echo $VARIABLE`** - Print variable value
- **`export VARIABLE=value`** - Set environment variable
- **`env`** - List all environment variables

## File Permissions

- **`chmod`** - Change file permissions
  - `chmod +x file` - Make file executable
  - `chmod 755 file` - Set specific permissions
- **`chown`** - Change file owner
- **`ls -l`** - View file permissions

## Package Management

### Ubuntu/Debian
- **`apt update`** - Update package list
- **`apt install package`** - Install package
- **`apt upgrade`** - Upgrade installed packages

### macOS (with Homebrew)
- **`brew install package`** - Install package
- **`brew update`** - Update Homebrew
- **`brew upgrade`** - Upgrade installed packages

## Troubleshooting

### Common Issues

1. **Permission Denied**
   - Use `sudo` for commands requiring root privileges
   - Check file permissions with `ls -l`

2. **Command Not Found**
   - Check if command is installed
   - Verify PATH environment variable
   - Use `which command` to find command location

3. **File Not Found**
   - Use `find` to locate files
   - Check current directory with `pwd`
   - Use `ls` to verify file exists

### Getting Help

- **`man command`** - Manual pages
- **`command --help`** - Built-in help
- **`info command`** - Info pages (if available)
- **`apropos keyword`** - Search manual pages by keyword

## Additional Resources

- [Linux Command Library](https://linuxcommandlibrary.com/)
- [Explain Shell](https://explainshell.com/) - Interactive command explanation
- [Unix/Linux Command Reference](https://ss64.com/bash/)
- [Bash Reference Manual](https://www.gnu.org/software/bash/manual/)
- [Advanced Bash-Scripting Guide](https://tldp.org/LDP/abs/html/)

## Embedded Development Resources

- [Raspberry Pi Pico SDK Documentation](https://www.raspberrypi.com/documentation/pico-sdk/)
- [ARM Cortex-M0+ Technical Reference Manual](https://developer.arm.com/documentation/ddi0484/c/)
- [Lingua Franca Documentation](https://www.lf-lang.org/docs/handbook/)
- [CMake Documentation](https://cmake.org/documentation/)
- [Git Documentation](https://git-scm.com/doc)
