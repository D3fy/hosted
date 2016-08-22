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

If the name is hosted locally the application will return 0
If it's not hosted it will return 1, if there is an error it
throws the string error to stdout and returns 2.

### example
This allows programmers to chain `hosted' into bash commands
```
  hosted www.google.com || echo "why would you be hosting google?"
```
