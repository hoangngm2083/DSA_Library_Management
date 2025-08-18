CXX = g++
CXXFLAGS = -std=c++17 -Iinclude -g
SRC = main.cpp \
      src/models/DanhMucSach.cpp \
      src/models/DauSach.cpp \
      src/models/MuonTra.cpp \
      src/models/TheDocGia.cpp \
      src/library.cpp

OUT = library

all:
	$(CXX) $(CXXFLAGS) $(SRC) -o $(OUT)

clean:
	rm -f $(OUT)
