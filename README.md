# rust-udp

## Testing

```bash
cargo run > /dev/null
nc -u ::1 1337
watch -n 0.1 'netstat -i | egrep "(lo)|(Iface)"'
cat /dev/urandom | nc -u ::1 1337 > /dev/null
```

110M/s http1.1 is possible with rpi4 - nice

https://www.youtube.com/watch?v=a-0PeuPINiQ
https://github.com/geerlingguy/raspberry-pi-pcie-devices/issues/3
https://github.com/geerlingguy/raspberry-pi-pcie-devices/issues/3#issuecomment-720086463

ethtool -C eth0 adaptive-tx on
sudo ethtool -C eth0 adaptive-rx on

ethtool -G ethN rx 4096 tx 4096

wrk -t 1 -c 50 -d 20s http://192.168.2.121
echo fffffff | sudo tee /sys/class/net/eth0/queues/rx-0/rps_cpus

echo fffffff | sudo tee /sys/class/net/eth0/queues/tx-*/xps_cpus


top
# press 1

cat /proc/interrupts | grep eth0

echo "0-3" | sudo tee /proc/irq/39/smp_affinity_list
echo "0-3" | sudo tee /proc/irq/40/smp_affinity_list

for irq in `grep eth0 /proc/interrupts | cut -d: -f1`; do \
    echo ffffff > /proc/irq/$irq/smp_affinity; \
done