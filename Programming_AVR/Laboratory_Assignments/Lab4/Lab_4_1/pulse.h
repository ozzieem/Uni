
typedef struct  
{
	char in;
	char in_old;
	char out;
} Pulse;

char pulse_run(Pulse* p, char in)
{
	p->in_old = p->in;
	p->in = in;
	p->out = p->in_old & !p->in;
	return p->out;
}