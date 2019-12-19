set ns [new Simulator]
set nf [open prog6.nam w]
$ns namtrace-all $nf
set tf [open prog6.tr w]
$ns trace-all $tf

proc finish {} {
	global ns nf tf
	$ns flush-trace
	close $nf
	close $tf

	exec nam prog6.nam &
	exec awk -f stats.awk prog6.tr &
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
$ns simplex-link $n2 $n3 0.3Mb 100ms DropTail
$ns simplex-link $n3 $n2 0.3Mb 100ms DropTail

set lan [$ns newLan "$n3 $n4 $n5" 0.5Mb 40ms LL Queue/DropTail MAC/802_3 Channel]




$ns duplex-link-op $n0 $n2 orient right-down
$ns duplex-link-op $n1 $n2 orient right-up
#change next two for xgraph bandwidhth
$ns simplex-link-op $n2 $n3 orient right
$ns simplex-link-op $n3 $n2 orient left

#Setup queue between n(2) and n(3) and monitor the queue
$ns queue-limit $n2 $n3 20
$ns simplex-link-op $n2 $n3 queuePos 0.5


#TCP-0 connect sink-4 ftp on tcp

set tcp0 [new Agent/TCP/Newreno]
$tcp0 set window_ 8000
$tcp0 set packetSize_ 552
$ns attach-agent $n0 $tcp0

set sink0 [new Agent/TCPSink/DelAck]
$ns attach-agent $n4 $sink0
$ns connect $tcp0 $sink0

set ftp0 [new Application/FTP]
$ftp0 attach-agent $tcp0



#UDP-1 connect sink-5 cbr on tcp 0.2mb 1000pktsize

set udp0 [new Agent/UDP]
$ns attach-agent $n1 $udp0

set null0 [new Agent/Null]
$ns attach-agent $n5 $null0
$ns connect $udp0 $null0

set cbr0 [new Application/Traffic/CBR]
$cbr0 set packetSize_ 1000
$cbr0 set rate_ 0.2Mb
$cbr0 set random_ false
$cbr0 attach-agent $udp0


set err [new ErrorModel]
$err set rate_ 0.0
$ns lossmodel $err $n2 $n3


$ns at 0.1 "$cbr0 start"
$ns at 1.0 "$ftp0 start"
$ns at 124.0 "$ftp0 stop"
$ns at 124.5 "$cbr0 stop"
$ns at 125.0 "finish"

#Run Simulation
$ns run