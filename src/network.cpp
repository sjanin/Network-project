#include "network.h"
#include <map>
#include <vector>
#include "random.h"
using namespace std;

void Network::resize(const size_t& n)
{
	values.clear(); 
	vector<double> newValues(n);
	values = newValues;
	RandomNumbers rng; 
	rng.normal(values,0,1);	 
}

bool Network::add_link(const size_t& a, const size_t& b) 
{

		if ((a < size()) and (b < size()) and (a!=b))
		{ 
			bool result(false);
			auto it=links.begin();
			for (it=links.begin();it!=links.end();it++)
			{
				if (((it->first) == a) and (it->second == b)) result=true; 
			}
			if (result==false)  
			{
				pair<size_t,size_t> x(a,b); 
				pair<size_t,size_t> y(b,a); 
				links.insert(x); 
				links.insert(y);
				return true;
			}else{
				return false;
			}
		}else{
			return false;
		} 
}

size_t Network::random_connect(const double& mean_deg) 
{
	links.clear(); 
	int counter(0);
	for (size_t i(0);i<values.size();++i) 
	{ 
		RandomNumbers rng;
		int N(rng.poisson(mean_deg)); 
		vector<int> othernodes(N);
		rng.uniform_int(othernodes,0,size()-1); 
		for (auto node : othernodes) 
		{
			if (add_link(i,node)) 
			{	counter+=1;
			}
		}
	}
	return counter; 
}


size_t Network::set_values(const std::vector<double>& newValues)
{	
	size_t n(newValues.size());
	if (n<size())
	{	vector<double> intermediateVector(size());
		for (size_t i(0); i<n; ++i)
		{
			intermediateVector[i]=newValues[i];
		}
		for (size_t j(n); j<size();++j)
		{
			intermediateVector[j]=values[j];
		}
		values=intermediateVector;
		return n;
	}else{
		for (size_t k(0); k<size(); ++k)
		{
			values[k]=newValues[k];
		}
		return size();
	}

}

size_t Network::size() const
{
	return values.size();
}

size_t Network::degree(const size_t& n) const
{
	size_t counter(0);
	auto it=links.begin();
	for (it=links.begin();it!=links.end();it++)
	{
		if (it->first == n) counter+=1; 
	}
	return counter;
		
}

double Network::value(const size_t &_n) const
{
	return values[_n];
}

std::vector<double> Network::sorted_values() const
{
	vector<double> sortedValues(values);
	sort (sortedValues.begin(),sortedValues.end(),greater<double>());
	return sortedValues;
}

std::vector<size_t> Network::neighbors(const size_t& n) const
{
	vector<size_t> neighbors;
	auto it=links.begin();
	for (it = links.begin();it != links.end();++it)
	{
		if ((it->first)==n) { neighbors.push_back(it->second); }
	}
	return neighbors;
}

