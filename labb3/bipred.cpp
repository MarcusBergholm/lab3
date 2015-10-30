#include <iostream>

using std::cin;
using std::cout;
using std::cerr;

void readBipartiteGraph() {
  int x, y, e;
  // Läs antal hörn och kanter
  cin >> x >> y >> e;

  // Läs in kanterna
  for (int i = 0; i < e; ++i) {
    int a, b;
    cin >> a >> b;
  }
}

void writeBipMatchSolution() {
  int x = 17, y = 4711, maxMatch = 0;

  // Skriv ut antal hörn och storleken på matchningen
  cout << x << " " << y << "\n" << maxMatch << "\n";

  for (int i = 0; i < maxMatch; ++i) {
    int a, b;
    // Kant mellan a och b ingår i vår matchningslösning
    cout << a << " " << b << "\n";
  }

}
