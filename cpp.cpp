// laz-perf.cpp
// javascript bindings for laz-perf
//

#include <iostream>

#include "streams.hpp"
#include "io.hpp"

class LASZip {
	typedef laszip::streams::memory_stream stream_type;
	typedef laszip::io::reader::basic_file<stream_type> reader_type;
	public:
		LASZip() : pmem_stream_(), pfile_() {}
		~LASZip() {
            pmem_stream_.reset();
            pfile_.reset();
        }

		void open(char* buf, size_t len) {
			pmem_stream_.reset(new stream_type(buf, len));
			pfile_.reset(new reader_type(*pmem_stream_));
		}

		void getPoint(char* pbuf) {
			pfile_->readPoint(pbuf);
		}

		unsigned int getCount() {
			return static_cast<unsigned int>(pfile_->get_header().point_count);
		}

	private:
		std::shared_ptr<stream_type> pmem_stream_;
		std::shared_ptr<reader_type> pfile_;
};

int main()
{
    auto getData([]()
    {
        std::vector<char> data;
        std::ifstream stream("wide-color.laz", std::ios::in | std::ios::binary);

        if (!stream.good()) throw std::runtime_error("Could not open file");
        stream.seekg(0, std::ios::end);
        data.resize(static_cast<std::size_t>(stream.tellg()));
        stream.seekg(0, std::ios::beg);
        stream.read(data.data(), data.size());
        stream.close();
        return data;
    });

    LASZip lz;
    auto data = getData();
    std::vector<char> p(34, 0);

    lz.open(data.data(), data.size());

    int32_t x, y, z;
    uint16_t r, g, b;
    for (std::size_t i(0); i < 3; ++i)
    {
        lz.getPoint(p.data());

        std::copy(p.data() + 0, p.data() + 4, reinterpret_cast<char*>(&x));
        std::copy(p.data() + 4, p.data() + 8, reinterpret_cast<char*>(&y));
        std::copy(p.data() + 8, p.data() + 12, reinterpret_cast<char*>(&z));

        std::copy(p.data() + 28, p.data() + 30, reinterpret_cast<char*>(&r));
        std::copy(p.data() + 30, p.data() + 32, reinterpret_cast<char*>(&g));
        std::copy(p.data() + 32, p.data() + 34, reinterpret_cast<char*>(&b));

        std::cout << "XYZ[" << i << "]: " <<
            x << " " << y << " " << z << std::endl;
        std::cout << "RGB[" << i << "]: " <<
            r << " " << g << " " << b << std::endl;
        std::cout << std::endl;
    }
}

