BEGIN {
	tcpc=0;
	udpc=0;
	tcpr=0;
	udpr=0;
}
{
	pkttype=$5;
	event=$1;
	if(pkttype=="tcp")
	{
	tcpc++;
	}
	if(pkttype=="cbr")
	{
	udpc++;
	}
	if(pkttype=="tcp" && event=="r" )
	{
	tcpr++;
	}
	if(pkttype=="cbr" && event=="r" )
	{
	udpr++;
	}
}
END {
	printf("TCP SENT %d \n",tcpc);
	printf("udp SENT %d \n",udpc);
	printf("TCP REC %d \n",tcpr);
	printf("udp REC %d \n",udpr);


}