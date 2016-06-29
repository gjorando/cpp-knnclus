#include "eknnwindev.h"

void EkNNExportToCSV(EkNNSystem *system, char *path)
{
	FILE *csv = NULL;
	if((csv = fopen(path, "w+")) == NULL)
	{
		fprintf(stderr, "fopen: unable to open %s\n", path);
		exit(1);
	}

	fprintf(csv, "N;K;C\n%lu;%lu;%lu\n", system->N, system->K, system->C);

	fprintf(csv, "\npoints\n;");
	for(unsigned long i = 0 ; i < system->N ; i++)
	{
		fprintf(csv, "%f%c", system->points[i].x, (i+1!=system->N?';':'\n'));
	}

	for(unsigned long c = 1 ; c <= system->C ; c++)
	{
		fprintf(csv, "%lu;", c);
		for(unsigned long i = 0 ; i < system->N ; i++)
		{
			if(c == system->points[i].cluster)
				fprintf(csv, "%f", system->points[i].y);
			fputc((i+1!=system->N?';':'\n'), csv);
		}
	}

	fprintf(csv, "\ndistances\n");
	for(unsigned long i = 0 ; i < system->N ; i++)
	{
		for(unsigned long j = 0 ; j < i ; j++)
		{
			fprintf(csv, "%f", system->distances[i][j]);
			fputc(';', csv);
		}
		fputs("0\n", csv);
	}

	fprintf(csv, "\nalpha\n");
	for(unsigned long i = 0 ; i < system->N ; i++)
		for(unsigned long j = 0 ; j < system->K ; j++)
			fprintf(csv, "%f%c", system->alpha[i][j], (j+1!=system->K?';':'\n'));

	fprintf(csv, "\nv\n");
	for(unsigned long i = 0 ; i < system->N ; i++)
		for(unsigned long j = 0 ; j < system->K ; j++)
			fprintf(csv, "%f%c", system->v[i][j], (j+1!=system->K?';':'\n'));

	fprintf(csv, "\nkNN\n");
	for(unsigned long i = 0 ; i < system->N ; i++)
		for(unsigned long j = 0 ; j < system->K ; j++)
			fprintf(csv, "%lu%c", system->kNN[i][j], (j+1!=system->K?';':'\n'));

	fclose(csv);
}
