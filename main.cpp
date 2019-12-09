#include <iostream>
#include <cstdlib>
#include <getopt.h>
#include "graph.h"

void print_help()
{
  std::cout << "Example usage:\n"
               "  ./run --problem 1 --undirected\n\n"
               "Options:\n"
               "  -p, --problem <NUM>\n"
               "  -u, --undirected\n"
               "  -h, --help\n";
}


int main(int argc, char *argv[])
{
  if (argc <= 1) {
    print_help();
    return 0;
  }

  unsigned long prob_no = 0;
  bool directed = true;

  int ch;
  while (true) {
    static struct option longopts[] = {
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
          char* tmp;
          prob_no = strtoul(optarg, &tmp, 10);
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

  if (optind == argc) {
    std::cerr << "No input file\n";
    return EXIT_FAILURE;
  } else if (optind == argc - 1) {
    // TODO: Handle input file
  } else {
    std::cerr << "More than one input files\n";
    return EXIT_FAILURE;
  }

  int pairs[] = {
    4, 0, 1,
    8, 1, 2,
    4, 2, 5,
    7, 3, 2,
    9, 3, 4,
    14, 3, 5,
    10, 4, 5,
    2, 6, 5,
    8, 7, 0,
    11, 7, 1,
    1, 7, 6,
    2, 8, 2,
    6, 8, 6,
    7, 8, 7
  };
  graph g(directed, 9, 14, pairs);
  std::cout << "Graph Input:\n" << g << "\n"
            << "====== Problem " << prob_no << " ======\n";
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

  return 0;
}
