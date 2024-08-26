// onnx_demo.cpp: определяет точку входа для приложения.
//

#include "onnx_demo.h"
#include "onnx/onnx_pb.h"
#include <fstream>
#include <cassert>

using namespace std;

void print_dim(const ::onnx::TensorShapeProto_Dimension& dim)
{
    switch (dim.value_case())
    {
    case onnx::TensorShapeProto_Dimension::ValueCase::kDimParam:
        std::cout << dim.dim_param();
        break;
    case onnx::TensorShapeProto_Dimension::ValueCase::kDimValue:
        std::cout << dim.dim_value();
        break;
    default:
        assert(false && "should never happen");
    }
}

void print_io_info(const ::google::protobuf::RepeatedPtrField< ::onnx::ValueInfoProto >& info)
{
    for (auto input_data : info)
    {
        auto shape = input_data.type().tensor_type().shape();
        std::cout << "  " << input_data.name() << ":";
        std::cout << "[";
        if (shape.dim_size() != 0)
        {
            int size = shape.dim_size();
            for (int i = 0; i < size - 1; ++i)
            {
                print_dim(shape.dim(i));
                std::cout << ", ";
            }
            print_dim(shape.dim(size - 1));
        }
        std::cout << "]\n";
    }
}



int main()
{
    //onnx::ModelProto model;
	//std::ifstream in("../test_model.onnx", std::ios_base::binary);
	//model.ParseFromIstream(&in);
	//in.close();
	//auto graph = model.graph();
	//cout << "Hello CMake." << endl;

    std::ifstream input("../test_model.onnx", std::ios::ate | std::ios::binary); // open file and move current position in file to the end

    std::streamsize size = input.tellg(); // get current position in file
    input.seekg(0, std::ios::beg); // move to start of file

    std::vector<char> buffer(size);
    input.read(buffer.data(), size); // read raw data

    onnx::ModelProto model;
    model.ParseFromArray(buffer.data(), size); // parse protobuf

    auto graph = model.graph();

    std::vector<std::string> initializer_name;
    for (auto initializer : graph.initializer()) {
        initializer_name.emplace_back(initializer.name());
    }

    for (auto input_data : graph.input()) {
        bool match = false;
        for (std::string n : initializer_name) {
            if (input_data.name().compare(n) == 0) {
                match = true;
                break;
            }
        }

    }

    for (auto output_data : graph.output()) {
        bool match = false;
        for (std::string n : initializer_name) {
            if (output_data.name().compare(n) == 0) {
                match = true;
                break;
            }
        }
    }

    std::cout << "graph inputs:\n";
    print_io_info(graph.input());

    std::cout << "graph outputs:\n";
    print_io_info(graph.output());
	return 0;
}
