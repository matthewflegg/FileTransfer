# File Transfer

A lightweight program that transfers files from a client to a server. This is free software under the GNU GPL v3.

Features
- Send a file to a server
- Save the file with a specified filename

Future features
- Encryption and auth
- Bidirectional transfer

## Usage

This program will only work on Linux.

- Compile the executables with `make`.
- Run the server:
```bash
./bin/server <server IP> <server port> <queue length>
```
- Run the client to send a file:
```bash
./bin/client <server IP> <server port> <path to outfile> <name to save file with> 
```

## Warning

This program is highly insecure as I haven't added many security features yet. Please
do not use this for anything serious.

Known security issues:
- No encryption during transfer
- No authentication (anyone can send a file to the server)
- Possible buffer overflow vulnerability

You can probably use this safely on a private home network with people you trust.
Encrypt your files before sending anything to the server.

This software is a prototype and should be treated as such.
