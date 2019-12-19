BEGIN {
	tcpdrop=0;
	udpdrop=0;
}
{
	event=$1;
	pkttype=$5;

	if(event=="d" && pkttype=="tcp")
		tcpdrop++;
	if(event=="d" && pkttype="cbr")
		udpdrop++;
}

END {
	printf(" tcpdrop:%d\n",tcpdrop);
	printf("udpdrop:%d\n",udpdrop );
}