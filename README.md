# rust-udp

## Testing

```bash
cargo run > /dev/null
nc -u ::1 1337
watch -n 0.1 'netstat -i | egrep "(lo)|(Iface)"'
cat /dev/urandom | nc -u ::1 1337 > /dev/null
```
