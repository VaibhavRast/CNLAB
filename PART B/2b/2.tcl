set ns [new Simulator]
set nf [open prog2.nam w]
$ns namtrace-all $nf
set tf [open prog2.tr w]
$ns trace-all $tf


proc finish {} {
global ns nf tf
$ns flush-trace
close $nf
close $tf

exec nam prog2.nam &
exec awk -f 2vp.awk prog2.tr &
exit 0
}


set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]

$ns duplex-link $n0 $n2 2Mb 10ms DropTail
$ns duplex-link $n1 $n2 2Mb 10ms DropTail
#change next two for xgraph bandwidhth
$ns simplex-link $n2 $n3 200Kb 10ms DropTail
$ns simplex-link $n3 $n2 200Kb 10ms DropTail


$ns queue-limit $n0 $n2 10
$ns simplex-link-op $n0 $n2 queuePos 0.5


#TCP-0 connect SINK-3 FTP ON TCP

set tcp0 [new Agent/TCP]
$ns attach-agent $n0 $tcp0

set sink0 [new Agent/TCPSink]
$ns attach-agent $n3 $sink0
$ns connect $tcp0 $sink0
$tcp0 set type_ FTP

set ftp0 [new Application/FTP]
$ftp0 attach-agent $tcp0

#TCP-1 CONNECT SINK-3 Telnet on TCP

set tcp1 [new Agent/TCP]
$ns attach-agent $n1 $tcp1

set sink1 [new Agent/TCPSink]
$ns attach-agent $n3 $sink1
$ns connect $tcp1 $sink1
$tcp1 set type_ Telnet


set telnet0 [new Application/Telnet]
$telnet0 attach-agent $tcp1


#schedule 
$ns at 0.5 "$telnet0 start"
$ns at 0.5 "$ftp0 start"
$ns at 24.5 "$ftp0 stop"
$ns at 24.5 "$telnet0 stop"
$ns at 25.0 "finish"

$ns run



