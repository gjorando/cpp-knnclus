#include "knnclus.h"

namespace kNN
{

System::System(double *p, unsigned long d, unsigned long n, unsigned long k)
{	
	N = n;
	K = k;
	C = n;
	D = d;

	points = new Point[N];
	for(unsigned long i = 0 ; i < N ; i++)
	{
		points[i].setDepth(D);
		for(unsigned long j = 0 ; j < D ; j++)
			points[i][j+1] = p[i*D+j];
	}
	initClusters();
	initDistances();
	initKNN();
	initGamma();
	initAlpha();
	initV();
}

void System::initClusters()
{
	unsigned long *clus = new unsigned long[N];

	for(unsigned long i = 0 ; i < N ; i++)
		clus[i] = i+1;

	Utils::toss(clus, N, 1.5*N);

	for(unsigned long i = 0 ; i < N ; i++)
		points[i].setCluster(clus[i]);

	delete[] clus;
}

void System::initDistances()
{
	double **dist = new double*[N];
	for(unsigned long i = 0 ; i < N ; i++)
		dist[i] = new double[N];

	for(unsigned long i = 0 ; i < N ; i++)
	{
		dist[i][i] = 0;
		for(unsigned long j = 0 ; j < i ; j++)
		{
			dist[i][j] = points[i].distance(points[j]);
			dist[j][i] = dist[i][j];
		}
	}

	distances = dist;
}

void System::initKNN()
{
	unsigned long **knn = new unsigned long*[N];
	for(unsigned long i = 0 ; i < N ; i++)
		knn[i] = new unsigned long[K];

	for(unsigned long i = 0 ; i < N ; i++)
	{
		double *tmpD = new double[N];

		for(unsigned long j = 0 ; j < N ; j++)
			tmpD[j] = distances[i][j];

		unsigned long *tmp = Utils::specialSort(tmpD, N);
		
		unsigned long j = 0, k = 0; 
		while(j < K)
		{
			if(tmpD[k] != 0)
			{
				knn[i][j] = tmp[k];
				j++;
			}
			k++;
		}

		delete[] tmpD;
		delete[] tmp;
	}

	kNN = knn;
}

void System::initGamma()
{
	double *dist;
	dist = new double[K*N];

	unsigned long cpt = 0;

	for(unsigned long i = 0 ; i < N ; i++)
		for(unsigned long j = 0 ; j < K ; j++)
			dist[cpt++] = distances[i][kNN[i][j]];

	gamma = 1/Utils::median(dist, K*N);

	delete[] dist;

}

void System::initAlpha()
{
	double **a = new double*[N];
	for(unsigned long i = 0 ; i < N ; i++)
		a[i] = new double[K];

	for(unsigned long i = 0 ; i < N ; i++)
		for(unsigned long j = 0 ; j < K ; j++)
			a[i][j] = exp(-gamma*distances[i][kNN[i][j]]*distances[i][kNN[i][j]]);

	alpha = a;
}

void System::initV()
{
	v = new double*[N];
	for(unsigned long i = 0 ; i < N ; i++)
		v[i] = new double[K];

	for(unsigned long i = 0 ; i < N ; i++)
		for(unsigned long j = 0 ; j < K ; j++)
			v[i][j] = -log(1-alpha[i][j]);
}

System::~System()
{
	delete[] points;
	for(unsigned long i = 0 ; i < N ; i++)
	{
		delete[] distances[i];
		delete[] kNN[i];
		delete[] alpha[i];
		delete[] v[i];
	}
	delete[] distances;
	delete[] kNN;
	delete[] alpha;
	delete[] v;
}

void System::clusterize()
{
	bool flag = true;
	unsigned long *sigma = new unsigned long[N];
	for(unsigned long i = 0 ; i < N ; i++)
		sigma[i] = i;

	unsigned long iter = 1;

	while(flag)
	{
		std::cout << "Iteration #" << iter << std::endl;

		flag = false;

		double **u = new double*[N];
		for(unsigned long i = 0 ; i < N ; i++)
		{
			u[i] = new double[C];
			for(unsigned long j = 0 ; j < C ; j++)
				u[i][j] = 0;
		}
		
		Utils::toss(sigma, N, 2*N);

		for(unsigned long i = 0 ; i < N ; i++)
		{
			std::cout << sigma[i] << "... ";

			double max = 0;
			unsigned long kstar = 1;

			for(unsigned long k = 0 ; k < C ; k++)
			{
				for(unsigned long j = 0 ; j < K ; j++)
					if(points[kNN[sigma[i]][j]].getCluster() == k+1)
						u[sigma[i]][k]+= v[sigma[i]][j];

				if(u[sigma[i]][k] >= max)
				{
					max = u[sigma[i]][k];
					kstar = k+1;
				}
			}

			if(points[sigma[i]].getCluster() != kstar)
			{
				points[sigma[i]].setCluster(kstar);
				flag = true;
			}
		}
		updateC();
		for(unsigned long i = 0 ; i < N ; i++)
			delete[] u[i];
		delete u;
	
		if(C == 1)
		{
			std::cerr << "EkNNClusterize: Gave only one cluster, please try again" << std::endl;
			exit(1);
		}

		std::cout << std::endl;
		iter++;
	}

	delete[] sigma;

}

void System::updateC()
{
	unsigned long *clus = new unsigned long[N];
	for(unsigned long i = 0 ; i < N ; i++)
		clus[i] = points[i].getCluster();

	Quicksort::quicksort((double*)clus, NULL, 0, N-1);

	//We kept C allocations because we need to use realloc
	unsigned long *distClus = (unsigned long*) malloc(sizeof(unsigned long));
	distClus[0] = clus[0];
	unsigned long c = 1;

	for(unsigned long i = 1 ; i < N ; i++)
		if(clus[i] != clus[i-1])
		{
			c++;
			distClus = (unsigned long*) realloc(distClus, c*sizeof(unsigned long));
			distClus[c-1] = clus[i];
		}

	for(unsigned long i = 0 ; i < N ; i++)
	{
		unsigned long oldClus = points[i].getCluster();
		unsigned long j = 0;
		while(oldClus!=distClus[j])
		{	
			j++;
			if(j>=c)
			{
				std::cerr << "EkNNUpdateC: Unexpected error" << std::endl;
				exit(2);
			}
		}
		points[i].setCluster(j+1);
	}

	C = c;

	delete[] clus;
	free(distClus);

}

void System::display()
{
	std::cout << "N=" << N << std::endl;
	std::cout << "K=" << K << std::endl;
	std::cout << "D=" << D << std::endl;
	std::cout << "C=" << C << std::endl;

	std::cout << std::endl << "points=" << std::endl;
	for(unsigned long i = 0 ; i < N ; i++)
	{
		for(unsigned long j = 0 ; j < D ; j++)
			std::cout << points[i][j+1] << ((j+1!=D)?":":"");
		std::cout << " | #" << points[i].getCluster() << std::endl;
	}

	std::cout << std::endl << "distances=" << std::endl;
	for(unsigned long i = 0 ; i < N ; i++)
	{
		for(unsigned long j = 0 ; j < N ; j++)
			std::cout << distances[i][j] << " ";
		std::cout << std::endl;
	}

	std::cout << std::endl << "kNN=" << std::endl;
	for(unsigned long i = 0 ; i < N ; i++)
	{
		for(unsigned long j = 0 ; j < K ; j++)
			std::cout << kNN[i][j] << " ";
		std::cout << std::endl;
	}

	std::cout << std::endl << "gamma=" << std::endl << gamma <<std::endl;

	std::cout << std::endl << "alpha=" << std::endl;
	for(unsigned long i = 0 ; i < N ; i++)
	{
		for(unsigned long j = 0 ; j < K ; j++)
			std::cout << alpha[i][j] << " ";
		std::cout << std::endl;
	}

	std::cout << std::endl << "v=" << std::endl;
	for(unsigned long i = 0 ; i < N ; i++)
	{
		for(unsigned long j = 0 ; j < K ; j++)
			std::cout << v[i][j] << " ";
		std::cout << std::endl;
	}
}

} // NAMESPACE EkNN
