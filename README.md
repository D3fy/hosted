# hosted

A quick and dirty application to resolve a DNS name and
determine if that address resolves locally.

The primary motiviation for writing hosted was to
determine if a floating/Virtual address is on the local
machine.

## building

### requirements

  * A compiler
  * POSIX
  * probably Linux
  * maybe BSD
  * potatoes
  * oh yea, gnu make
  * love
  * jk computers don't love

### compiling

```
  make
```

## usage

```
   hosted <qualified domain name>
```

If the name is hosted locally the application will say
as much. If it's not hosted it will not have any output.
If there is an error it will throw the string error and set
a return code other than zero.
