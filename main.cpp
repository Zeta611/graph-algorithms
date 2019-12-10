#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <getopt.h>
#include "graph.h"

void print_help()
{
  std::cout << "Example usage:\n"
               "  ./run input_file --problem 1 --undirected\n\n"
               "Options:\n"
               "  -p, --problem <NUM>\n"
               "  -u, --undirected\n"
               "  -h, --help\n";
}


std::string trim(const std::string& str)
{
    size_t first = str.find_first_not_of(' ');
    if (std::string::npos == first) { return str; }
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, last - first + 1);
}


bool parse(const std::string& fname, int& v, int& e, int*& pairs)
{
  std::ifstream input {fname};

  if (input.is_open()) {
    std::string line;

    // The first line should contain the total number of vertices
    if (std::getline(input, line)) {
      v = std::stoi(line);
    } else {
      return false;
    }

    // The second line should contain the total number of edges
    if (std::getline(input, line)) {
      e = std::stoi(line);
    } else {
      return false;
    }

    pairs = new int[3 * e];
    int lcnt {0};
    int i {0};
    while (std::getline(input, line)) {
      ++lcnt;
      // Get the whole line first
      std::istringstream ss {line};
      while (std::getline(ss, line, ',')) {
        if (i >= 3 * e) { return false; }
        pairs[i++] = std::stoi(line);
      }
    }
    input.close();

    if (lcnt != e) {
      delete[] pairs;
      return false;
    }
  } else {
    delete[] pairs;
    return false;
  }
  return true;
}


int main(int argc, char *argv[])
{
  if (argc == 1) {
    print_help();
    return EXIT_FAILURE;
  }

  // Selected problem number
  unsigned long prob_no {0};

  // Flag for using a directed or undirected graph
  bool directed {true};

  int ch;
  bool found_problem_op {false};
  while (true) {
    static struct option longopts[] {
      { "problem",    required_argument, NULL, 'p' },
      { "undirected", no_argument,       NULL, 'u' },
      { "help",       no_argument,       NULL, 'h' },
      { NULL,         0,                 NULL, 0 }
    };

    ch = getopt_long(argc, argv, "p:u::h", longopts, NULL);

    if (ch == -1) { break; }
    switch (ch) {
      case 'h':
        print_help();
        return 0;

      case 'p': {
          found_problem_op = true;
          char* tmp;
          prob_no = std::strtoul(optarg, &tmp, 10);
          if (!(optarg != tmp && *tmp == '\0' && prob_no <= 4)) {
            std::cerr << "Problem number should be either 1, 2, 3, or 4\n";
            return EXIT_FAILURE;
          }
        }
        break;

      case 'u':
        directed = false;
        break;

      default: return EXIT_FAILURE;
    }
  }

  if (!found_problem_op) {
    std::cerr << "No problem selected\n";
    return EXIT_FAILURE;
  }

  int v, e;
  int* pairs;

  // Handle an input file
  if (optind == argc) {
    std::cerr << "No input file\n";
    return EXIT_FAILURE;

  } else if (optind == argc - 1) {
    std::string fname {argv[optind]};

    bool success {parse(fname, v, e, pairs)};
    if (!success) {
      std::cerr << "Invalid input file: " << fname << "\n";
      return EXIT_FAILURE;
    }

  } else {
    std::cerr << "More than one input files\n";
    return EXIT_FAILURE;
  }

  graph g(directed, v, e, pairs);
  std::cout << "Graph Input:\n" << g
            << "\n====== Problem " << prob_no << " ======\n";

  switch (prob_no) {
    case 1:
      std::cout << "DFS: ";
      g.dfs();
      break;

    case 2:
      int src;
      std::cout << "Enter source vertex: ";
      std::cin >> src;
      std::cout << "BFS from " << src << ": ";
      g.bfs(src);
      break;

    default: return EXIT_FAILURE;
  }

  delete[] pairs;
  return 0;
}
