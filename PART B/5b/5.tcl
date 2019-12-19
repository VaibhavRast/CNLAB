set ns [new Simulator]
set nf [open prog5.nam w]
$ns namtrace-all $nf
set tf [open prog5.tr w]
$ns trace-all $tf


proc finish {} {
global ns nf tf
$ns flush-trace
close $nf
close $tf

exec nam prog5.nam &
exec awk -f 5.awk prog5.tr &
exit 0
}


set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]
set n4 [$ns node]
set n5 [$ns node]


$ns duplex-link $n0 $n2 2Mb 10ms DropTail
$ns duplex-link $n1 $n2 2Mb 10ms DropTail
#change next two for xgraph bandwidhth
$ns simplex-link $n2 $n3 1Mb 100ms DropTail
$ns simplex-link $n3 $n2 1Mb 100ms DropTail


$ns duplex-link-op $n0 $n2 orient right-down
$ns duplex-link-op $n1 $n2 orient right-up
#change next two for xgraph bandwidhth
$ns simplex-link-op $n2 $n3 orient right
$ns simplex-link-op $n3 $n2 orient left


#$ns queue-limit $n0 $n2 10
#$ns simplex-link-op $n0 $n2 queuePos 0.5
 #0415

set lan [$ns newLan "$n3 $n4 $n5" 0.5Mb 40ms LL Queue/DropTail MAC/Csma/Cd Channel]

$n0 label TCP_TRAFFIC
$n1 label UDP_TRAFFIC
# TCP-0 CONNECT SINK-4 ftp on tcp

set tcp0 [new Agent/TCP/Newreno]
$ns attach-agent $n0 $tcp0

set sink0 [new Agent/TCPSink/DelAck]
$ns attach-agent $n4 $sink0
$ns connect $tcp0 $sink0
$tcp0 set packetSize_ 552

set ftp0 [new Application/FTP]
$ftp0 attach-agent $tcp0


#UDP-1 connect sink-5 cbr on udp

set udp0 [new Agent/UDP]
$ns attach-agent $n1 $udp0

set null0 [new Agent/Null]
$ns attach-agent $n5 $null0
$ns connect $udp0 $null0

set cbr0 [new Application/Traffic/CBR]
$cbr0 set packetSize_ 1000
$cbr0 set rate_ 0.05Mb
$cbr0 set random_ false
$cbr0 attach-agent $udp0

#run schedule
$ns at 0.3 "$cbr0 start"
$ns at 0.5 "$ftp0 start"
$ns at 7.0 "$ftp0 stop"
$ns at 7.5 "$cbr0 stop"
$ns at 8.0 "finish"

$ns run

