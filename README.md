# sys-ftpd

This is a nintendo-switch sysmodule which runs an ftpd-server in the background (on port 5000 with no auth).

The key difference between sys-ftpd-light and [sys-ftpd](https://github.com/jakibaki/sys-ftpd) is that it applies a lot of changes to significantly reduce memory usage (from ~7MB to ~1MB). This includes removing all sound effects and reducing the buffer size reserved for the ftpd server.

Hotkeys: To help with security while there is are no login credentials, debugging, or otherwise, you can toggle the state of the server using the (+) + (-) + (X) button combination.

---

Config Example (Located on your sd in `sdmc:/config/sys-ftpd-10k/config.ini`):

```
[User]
user:=ftpd

# user:= -> Login username

[Password]
password:=12345

# password:= -> Login password

[Port]
port:=5000

# port:=5000 -> opens the server on port 5000 (using the console's IP address).

[Anonymous]
anonymous:=1

# anonymous:=1 -> Allows logging into the ftpd server without username or password.
# anonymous:=0 -> Only allows logging into the ftpd server with the correct username and password. user and password (in fields above) must be set.

[Pause]
disabled:=0
keycombo:=PLUS+MINUS+X

# disabled:=1 -> Disables allowing sys-ftpd to be paused by pressing the key combination.
# disabled:=0 -> Allows sys-ftpd to be paused by pressing the key combination.
# keycombo:=  -> The key combination used to pause sys-ftpd. Each key is separated by either a plus '+' or a space ' '. Up to 8 keys are allowed.
# The list of valid keys is as follows:
# A, B, X, Y, LS, RS, L, R, ZL, ZR, PLUS, MINUS, DLEFT, DUP, DRIGHT, DDOWN

[LED]
led:=1

# led:=1 -> LED flashes on connect (default)
# led:=0 -> LED does not flash on connect
```
