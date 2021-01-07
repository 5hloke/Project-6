#include "catch.hpp"
#include "treap_bst.hpp"

// Methods and empty() and remove() tested extensively in other test cases 
TEST_CASE("Testing the rndgen fucnction") {
	std::random_device rd;
	std::mt19937 rand;
	std::mt19937::result_type prior;

	
	for (int i = 0; i < 5; i++) {
		prior = rand() % 200;
		std::cout << prior << std::endl;
	}

	TreapBST<int, std::string> t;
	int x = 8;
	bool found = true;
	bool found2 = true;
	t.insert(5, "a");
	//t.insert(5, "b");
	t.insert(4, "b");
	t.insert(3, "c");
	t.insert(2, "d");
	t.insert(6, "e");
	t.insert(7, "f");
	t.insert(8, "g");
	t.insert(9, "h");
	t.insert(10, "i");
	//t.insert(10, "k");
	/*t.insert(4, "b");
	t.insert(1, "c");
	t.insert(11, "d");
	t.insert(25, "e");
	t.insert(45, "f");
	t.insert(50, "g");
	t.insert(12, "h");
	t.insert(55, "i");
	t.insert(10, "j");
	t.insert(3, "k");
	t.insert(2, "l");
	t.insert(7, "m");
	t.insert(8, "n");
	t.insert(9, "o");
	t.insert(70, "p");*/
	t.remove(8);
	//t.remove(5);
	//t.remove(1);
	//REQUIRE(t.empty());
	std::cout << t.search(5, found) << std::endl;
	//REQUIRE(!found);
	std::cout << "Height: " << int(t.height()) << std::endl;
	REQUIRE(found);
	//t.~TreapBST();
	TreapBST<int, std::string> t2;
	TreapBST<int, std::string> t3;
	t2 = t3;
//	std::cout << "t2: " << (t2.search(5, found2)) << std::endl;
//	//REQUIRE(t.height() == 0);
//	//t.search(5, found2);
//	t2.remove(5);
//	t2.search(5, found2);
//	t.search(5, found);
//	REQUIRE(found);
//	REQUIRE(!found2);
////	REQUIRE(t.empty());
	
}

// implicitly testing the isEmpty MEthod 
TEST_CASE("Testing the Default constructor")
{
	TreapBST<int, int> t;
	REQUIRE(t.empty());
	REQUIRE(t.height() == 0);

}

// implicitly testing the insert(), remove, empty(), height() method
TEST_CASE("Testing the parameterized constructor")
{
	TreapBST<int, int> t;
	bool found = false;
	int x = 0;
	REQUIRE(t.empty());
	t.insert(1, 2);
	t.insert(2, 15);
	t.insert(4, 100);
	t.insert(9, 50);
	t.insert(15, 78);
	t.insert(0, 65);
	t.insert(25, 45);
	t.insert(80, 90);
	REQUIRE(t.height() == 7);
	REQUIRE(!t.empty());
	REQUIRE(t.search(x, found) == 65);
	REQUIRE(found);
	t.remove(15);
	t.search(15, found);
	REQUIRE(!found);
	
	TreapBST<int, int> t2(t);
	REQUIRE(t2.height() == 6);
	REQUIRE(!t2.empty());
	REQUIRE(t2.search(x, found) == 65);
	REQUIRE(found);
	
}

TEST_CASE("Testong the copy assignment operator")
{
	TreapBST<int, int> t;
	bool found = false;
	int x = 0;
	REQUIRE(t.empty());
	t.insert(1, 2);
	t.insert(2, 15);
	t.insert(4, 100);
	t.insert(9, 50);
	t.insert(15, 78);
	t.insert(0, 65);
	t.insert(25, 45);
	t.insert(80, 90);
	REQUIRE(t.height() == 7);
	REQUIRE(!t.empty());
	REQUIRE(t.search(x, found) == 65);
	REQUIRE(found);
	t.remove(15);
	t.search(15, found);
	REQUIRE(!found);

	TreapBST<int, int> t2;
	t2 = t;
	REQUIRE(t2.height() == 6);
	REQUIRE(!t2.empty());
	REQUIRE(t2.search(x, found) == 65);
	REQUIRE(found);
}

// Case when the same key is reentered
TEST_CASE("Testing the insert method")
{
	TreapBST<int, int> t; 
	t.insert(1, 2);
	t.insert(2, 15);
	t.insert(4, 100);
	t.insert(9, 50);
	t.insert(15, 78);
	t.insert(0, 65);
	t.insert(25, 45);
	t.insert(80, 90);
	REQUIRE(t.height() == 7);
	REQUIRE_THROWS_AS(t.insert(0, 50), std::logic_error);
	REQUIRE_THROWS_AS(t.insert(1, 50), std::logic_error);
	REQUIRE_THROWS_AS(t.insert(4, 50), std::logic_error);
	REQUIRE(t.height() == 7);
}

// Checking the logic error thrown when removing from an empty treap 
TEST_CASE("testing the remove method")
{
	TreapBST<int, int> t;
	REQUIRE(t.empty());
	REQUIRE(t.height() == 0);
	REQUIRE_THROWS_AS(t.remove(5), std::logic_error);
}

TEST_CASE("Testing the search method")
{
	TreapBST<int, int> t;
	REQUIRE_THROWS_AS(t.remove(5), std::logic_error);
	bool found = false, found1 = false, found2 = false, found3 = false, found4 = false, found5 = false;
	int x = 15, x1 = 0, x2 = 9, x3 = 1, x4 = 80, x5 = 25;
	t.insert(1, 2);
	t.insert(2, 15);
	t.insert(4, 100);
	t.insert(9, 50);
	t.insert(15, 78);
	t.insert(0, 65);
	t.insert(25, 45);
	t.insert(80, 90);
	REQUIRE(t.height() == 7);
	REQUIRE(t.search(x, found) == 78);
	REQUIRE(t.search(x1, found1) == 65);
	REQUIRE(t.search(x2, found2) == 50);
	REQUIRE(t.search(x3, found3) == 2);
	REQUIRE(t.search(x4, found4) == 90);
	REQUIRE(t.search(x5, found5) == 45);
	REQUIRE(found);
	REQUIRE(found1);
	REQUIRE(found2);
	REQUIRE(found3);
	REQUIRE(found4);
	REQUIRE(found5);
	t.remove(x);
	t.remove(x3);
	t.remove(x5);
	t.search(x, found);
	t.search(x3, found3);
	t.search(x5, found5);
	REQUIRE(!found);
	REQUIRE(!found3);
	REQUIRE(!found5);
	REQUIRE(t.height() == 5);
	REQUIRE(!t.empty());

}