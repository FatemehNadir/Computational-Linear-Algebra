#include <pybind11/pybind11.h>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <pybind11/stl.h>
namespace py = pybind11;

long int add(std::vector <long int> &arr) {
long int sum=0;

	for(auto i : arr)
		sum+=i;

return sum;
}



PYBIND11_MODULE(sumarr, m) {
    

    m.def("add", &add);
	


#ifdef VERSION_INFO
    m.attr("__version__") = MACRO_STRINGIFY(VERSION_INFO);
#else
    m.attr("__version__") = "dev";
#endif
}
