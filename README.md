# cslocate

v0.0.1 

## What is this?

`cslocate` is a simple command-line utility for Linux and similar platforms, that attempts to find the location (country or region) corresponding to an amateur radio callsign. It can either print the best match -- as it understands it -- or all potential matches.  

Of course, there are many potential ways to look up a callsign in online databases. This program is specifically written to work without Internet access -- for portable radio operation, for eample.

The program is written in ANSI-standard C, and should build easily on any Linux-like system with gcc or a similar C compiler.

## Usage

To find the location of callsign, run `cslocate` like this:

    $ cslocate m6KXB 
    M6KXB: England, Foundation License

Note that callsigns are not case-sensitive, although they are usually written with upper-case letters.

To list all potential matching locations, use the `-a` (or `--all`) switch:

    $ cslocate --all EA5XX 
    EA5XX: (3) Spain, Valencia (HF)
    EA5XX: (3) Spain, Valencia (Full License)
    EA5XX: (2) Spain

The number in brackets is the number of characters in the supplied callsign that matched the callsign template for the location. Generally, a larger number indicates a better match.

To print the minimum amount of information -- just the country and nothing
else:

  $ cslocate -q M6KXB
  England

## Building the program

Get the C source code from https://github.com/kevinboone/cslocate.

If your system has `curl` and `perl`, do 

    $ ./scripts/get_data.sh

To download and parse the latest data files. If not, you can use the versions supplied with the program, although they may be out of date.

Then

    $ make
    $ sudo make install

## Limitations

Many callsigns are genuinely ambgiguous, partly because national boundaries have a certain fluidity. Accuracy cannot be guaranteed. 

The program does not even attempt to determine whether a callsign has ever been issued, or even if it is valid -- it just matches the characters against a set of templates.

Sometimes the `--all` switch will cause the same data to be displayed more than once, if multiple templates match.

The `-q` switch will attempt to parse the country name out of the supplied licence description. However, this will not always succeed -- the data the program uses specifically describes regions, and parsing out just the country is not a well-defined process.

## Author and copyright

`cslocate` is written and maintained by Kevin Boone, but it uses data provided by Martin Kratoska and others as part of the CQRLog project. The CQRLog files are open source under the terms of the GPL, version 2.0; this utility is open souce under the terms of the GPL, version 3.0.

Please report bugs, etc., to kevin@bearontheair.co.uk

