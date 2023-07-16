# Install Lingua Franca

As this project is under development, we cannot use a release of Lingua Franca, but must currently use a branch obtained from GitHub.  These instructions are adapted from the [developer setup instructions](https://www.lf-lang.org/docs/handbook/developer-setup).

To start, clone the repository:

```
git clone git@github.com:lf-lang/lingua-franca.git
cd lingua-franca
git submodule update --init --recursive
```

## Install Java, gradle, and cmake

If you have Java installed already, check that the version is at least 17:

```
$ java -version
java version "17.0.3" 2022-04-19 LTS
```

If not, [update your version of Java](https://www.java.com/en/download/).

Make sure you have `gradle` and `cmake` (the build tools used by LF).  On a Mac:

```
brew install gradle cmake
```

## Switch to the pico Branch

The setup currently uses the [pico](https://github.com/lf-lang/lingua-franca/tree/pico) branch of LF.

```
git fetch
git checkout pico
```

## Put the LF Tools in your PATH

Add the `lingua-franca/bin` directory to your  `PATH` environment variable:

```
export PATH=../lingua-franca/bin:${PATH}
```

where `...` is replaced by the path to the folder where you cloned the `lingua-franca` repository.  For convenience, put the above command in your `~/.bash_profile` file so that the environment variable is available to any bash terminal.

## Compile the LF Tools

Invoking the `lfc` compiler will automatically build the compiler if it is not up to date.  If you have set your path as above, you can simply do this:

```
lfc --version
```

After a while, this should print something like:

```
lfc 0.4.1-SNAPSHOT
```

To test the compiler and the tools, compile and run one of the LF test programs. For example,

```
cd .../lingua-franca/test/C
lfc src/HelloWorld.lf
bin/HelloWorld
```

The second line compiles a "Hello World" program, and the third line runs the compiled program.
