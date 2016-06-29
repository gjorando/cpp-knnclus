#include "eknnwindev.h"

void EkNNExportToCSV(EkNNSystem *system, char *path)
{
	FILE *csv = NULL;
	if((csv = fopen(path, "w+")) == NULL)
	{
		fprintf(stderr, "fopen: unable to open %s\n", path);
		exit(1);
	}

	fprintf(csv, "points;");
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

	fclose(csv);
}
