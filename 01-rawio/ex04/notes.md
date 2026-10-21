

Ls config:
1. If it is a file -> -, A link -> l, a directory -> d
2. Permisions.
3. N hardlinks.
4. Owner. 1*
5. File group (need to investigate).
6. File size.
7. Last mod time. 2*
8. File name.

1* if user or group does not exist, put the GID.
2* If the date is 6 months appart from today (back or forward), put the year.