#include <iostream>
#include <vector>
#include <boost/thread/thread.hpp>


class Foo {
public:

  Foo(int size) : results(size, 0.0f), data(size, 1.0f) {}

  void parfor() {
    std::vector<boost::thread> grp;
    for (int i = 0; i < data.size(); i++)
      grp.push_back(boost::thread(&Foo::work, this, i));
    // work(i);

    for (int i = 0; i < grp.size(); i++)
      grp[i].join();

    for (int i = 0; i < results.size(); i++)
      std::cout << "i=" << i << " result=" << results[i] << std::endl;
  }

  void work(int i) {
    for (int j = 0; j < i; j++)
      results[i] += data[j];
  }

  std::vector<float> results;
  std::vector<float> data;
};

int main(int argc, char **argv) {
  Foo f(10);
  f.parfor();
}
