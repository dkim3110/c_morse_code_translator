# CLI Morse Code Translator

## DESCRIPTION:

A simple command-line utility to translate Morse code to and from English.

## INSTALLATION:

```bash
# Build
git clone
cd c_morse_code_translator
make

# Deploy
sudo make install
# To uninstall, run 'sudo make uninstall'
```

## USAGE:

```bash
# Rename TARGET variable in Makefile to change binary name
cmorse [flag] string to translate
cmorse string to translate [flag]
```

## FLAGS:

`-h, --help`: Prints help message; overrides all arguments

`-m, --morse`: Translates Morse code into English; must not contain alphanumeric characters

`[no flags]`: Translates English into Morse code; ignores non-alphanumeric characters
