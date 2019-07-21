#include <cstdio>
#include <cstring>
#include <string>
#define PRIME 127
#define HASH 256

int check_sys()
{
	int num = 1;
	if (*(char *)&num == 1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}


#define swab64(x) \
((uint64_t)(\
(((uint64_t)(x)& (uint64_t)0x00000000000000ffULL) << 56) | \
(((uint64_t)(x)& (uint64_t)0x000000000000ff00ULL) << 40) | \
(((uint64_t)(x)& (uint64_t)0x0000000000ff0000ULL) << 24) | \
(((uint64_t)(x)& (uint64_t)0x00000000ff000000ULL) << 8) | \
(((uint64_t)(x)& (uint64_t)0x000000ff00000000ULL) >> 8) | \
(((uint64_t)(x)& (uint64_t)0x0000ff0000000000ULL) >> 24) | \
(((uint64_t)(x)& (uint64_t)0x00ff000000000000ULL) >> 40) | \
(((uint64_t)(x)& (uint64_t)0xff00000000000000ULL) >> 56)))

uint64_t htonll(uint64_t x)

{
	return swab64(x);

}

double htond(double x)
{
	double ret;
	uint64_t t = htonll(*(uint64_t*)&x);
	ret = *(double *)&t;
	return ret;
}


uint64_t ntohll(uint64_t x)

{
	return htonll(x);
}



int main()
{
	//double test = 0x4016ae147ae147ae;
	double test =100.0;
	
	printf("before convert:\n");
	for (int i = 0; i<sizeof(test); i++)
	{
		printf("%x ", *(((char*)&test) + i));
	}
	printf("\n");
	
	test = htond(test);

	printf("\n");
	printf("after convert:\n");
	for (int i = 0; i<sizeof(test); i++)
	{
		printf("%x ", *(((char*)&test) + i));
	}
	printf("\n");

	//if (check_sys() == 1)
	//{
	//	printf("little\n");
	//}
	//else
	//{
	//	printf("big\n");
	//}
	return 0;
}