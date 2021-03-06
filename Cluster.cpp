#include <iostream>
#include <vector>

#include "Cluster.h"
#include "Vector.h"

Cluster::Cluster(Vector * centroid){
  Centroid=centroid;
}

Cluster::~Cluster(){

  Vectors_in_Cluster.erase(Vectors_in_Cluster.begin(),Vectors_in_Cluster.end());
  if(Centroid->get_identity().compare(0,2,"CL")==0)
  {
    delete Centroid;
  }
}

void Cluster::add_Vector(Vector * vector){

  Vectors_in_Cluster.insert (Vectors_in_Cluster.end(),vector);
}

Vector * Cluster::get_centroid(){

  return Centroid;
}

std::string Cluster::get_centroid_id(){

  return Centroid->get_identity();
}



int Cluster::update_Centroid(Vector * centroid){

  int r=0;
  if(centroid->get_identity().compare(0,2,"CL")==0)
  {
  std::vector<coordinate> * co=Centroid->get_coordinates();
  coordinate *val= new long double[co->size()];

  for(int i=0;i<co->size();i++){ //take values of centroid
    val[i]=co->at(i);
  }

  for(int i=0;i<Vectors_in_Cluster.size();i++){ //for every other vector in the cluster
    co=Vectors_in_Cluster.at(i)->get_coordinates();

    for(int j=0;j<co->size();j++){//add their values
      val[j]=val[j]+co->at(j);
    }
  }

  for(int j=0;j<co->size();j++){
   val[j]=val[j]/(long double)(Vectors_in_Cluster.size()+1); //and take the average
  }

  for(int j=0;j<co->size();j++){ //this is the new centroid for the cluster 
    if(co->at(j)!=val[j])
      r=1;
    centroid->add_coordinate(val[j]);
  }

  if(Centroid->get_identity().compare(0,2,"CL")==0)
    delete Centroid;

    Centroid=centroid;
    delete[] val;
}
else
  Centroid=centroid;
  return r;

}

std::vector<Vector *> * Cluster::get_cluster_vectors(){

  return &Vectors_in_Cluster;
}

void Cluster::empty_vectors_in_cluster(){
  Vectors_in_Cluster.clear();
}
