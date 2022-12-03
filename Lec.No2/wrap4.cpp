<%
cfg['compiler_args'] = ['-std=c++11', '-fopenmp']
cfg['linker_args'] = ['-lgomp']
setup_pybind11(cfg)
%>

#include <omp.h>
#include <iostream>
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

#define numOfth 3

namespace py = pybind11;

long int sum(py::array_t<int> input1) {
    auto buf1 = input1.request();

    if (buf1.ndim != 1 )
        throw std::runtime_error("Number of dimensions must be one");

    auto result = py::array(py::buffer_info(
        nullptr,            /* Pointer to data (nullptr -> ask NumPy to allocate!) */
        sizeof(int),     /* Size of one item */
        py::format_descriptor<int>::value, /* Buffer format */
        buf1.ndim,          /* How many dimensions? */
        { buf1.shape[0] },  /* Number of elements for each dimension */
        { sizeof(int) }  /* Strides for each dimension */
    ));

   

    int *ptr1 = (int *) buf1.ptr;
    long int s =0;
    for (size_t idx = 0; idx < buf1.shape[0]; idx++)
        s+= ptr1[idx] ;

    return s;
};



long int summp(py::array_t<int> input1) {
    py::gil_scoped_acquire acquire;
    auto buf1 = input1.request();

    if (buf1.ndim != 1 )
        throw std::runtime_error("Number of dimensions must be one");

 
    int *ptr1 = (int *) buf1.ptr;
    long int res = 0;

    omp_set_num_threads(numOfth);

    #pragma omp parallel for
    	for (int idx = 0 ; idx < buf1.shape[0] ; idx++)
		res += ptr1[idx];
    
	return res;
}



PYBIND11_MODULE(wrap4, m) {
    m.def("sum", &sum, "Add two NumPy arrays");
    m.def("summp", [](py::array_t<int> &input1) {
      /* Release GIL before calling into C++ code */
      py::gil_scoped_release release;
      return summp(input1);
    });
}
