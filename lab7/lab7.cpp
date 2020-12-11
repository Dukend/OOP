// by Dukend
#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <fstream>
#include <stack>
#include <ctime>
#include <cstdlib>
#include <cmath>

struct Cords{
	double x, y;
};
std::istream &operator>>(std::istream &is, Cords &c){
	is >> c.x >> c.y;
	return is;
}
std::istream &operator>>(std::istream &is, std::vector<Cords> &v){
	for (size_t i = 0; i < v.size(); i++){
		std::cin >> v[i];
	}
	return is;
}
std::ostream &operator<<(std::ostream &os, Cords c){
	os << "<" << c.x << ", " << c.y << ">";
	return os;
}
class Figure{
public:
	std::vector<Cords> cords;

	Figure() {}
	Figure(const Figure &f){
		for (size_t i = 0; i < f.cords.size(); i++){
			cords.push_back(f.cords[i]);
		}
	}
	virtual ~Figure() {}

	void read_cords(){
		for (size_t i = 0; i < cords.size(); i++){
			std::cin >> cords[i];
		}
	}

	virtual void print_name() = 0;
	virtual char get_figure() = 0;

	void print(){
		print_name();
		for (size_t i = 0; i < cords.size(); i++){
			std::cout << cords[i] << " ";
		}
		std::cout << '\n';
	}
};

class Square : public Figure{
public:
	Square(){
		for (size_t i = 0; i < 4; i++){
			cords.push_back({0, 0});
		}
	}
	Square(const Cords &c1, const Cords &c2, const Cords &c3, const Cords &c4){
		cords.push_back(c1);
		cords.push_back(c2);
		cords.push_back(c3);
		cords.push_back(c4);
	}
	Square(const Square &s){
		cords = s.cords;
	}
	Square(const std::vector<Cords> &v){
		cords = v;
	}
	~Square() {}

	void print_name(){
		std::cout << "Square: ";
	}

	char get_figure(){
		return 's';
	}
};

class Rectangle : public Figure{
public:
	Rectangle(){
		for (size_t i = 0; i < 4; i++){
			cords.push_back({0, 0});
		}
	}
	Rectangle(const Cords &c1, const Cords &c2, const Cords &c3, const Cords &c4){
		cords.push_back(c1);
		cords.push_back(c2);
		cords.push_back(c3);
		cords.push_back(c4);
	}
	Rectangle(const Rectangle &r){
		cords = r.cords;
	}
	Rectangle(const std::vector<Cords> &v){
		cords = v;
	}
	~Rectangle() {}

	void print_name(){
		std::cout << "Rectangle: ";
	}

	char get_figure(){
		return 'r';
	}
};

class Trapezoid : public Figure{
public:
	Trapezoid(){
		for (size_t i = 0; i < 4; i++){
			cords.push_back({0, 0});
		}
	}
	Trapezoid(const Cords &c1, const Cords &c2, const Cords &c3, const Cords &c4){
		cords.push_back(c1);
		cords.push_back(c2);
		cords.push_back(c3);
		cords.push_back(c4);
	}
	Trapezoid(const Trapezoid &t){
		cords = t.cords;
	}
	Trapezoid(const std::vector<Cords> &v){
		cords = v;
	}
	~Trapezoid() {}

	void print_name(){
		std::cout << "Trapezoid: ";
	}

	char get_figure(){
		return 't';
	}
};

class Factory{
public:
	virtual Figure *create_figure() = 0;
	virtual ~Factory() {}
};

class Square_Factory : public Factory{
public:
	Figure *create_figure(){
		return reinterpret_cast<Figure *>(new Square());
	}
	Figure *create_figure(const Cords &c1, const Cords &c2, const Cords &c3, const Cords &c4){
		return reinterpret_cast<Figure *>(new Square(c1, c2, c3, c4));
	}
	Figure *create_figure(const std::vector<Cords> &v){
		return reinterpret_cast<Figure *>(new Square(v));
	}
};

class Rectangle_Factory : public Factory{
public:
	Figure *create_figure(){
		return reinterpret_cast<Figure *>(new Rectangle());
	}
	Figure *create_figure(const Cords &c1, const Cords &c2, const Cords &c3, const Cords &c4){
		return reinterpret_cast<Figure *>(new Rectangle(c1, c2, c3, c4));
	}
	Figure *create_figure(const std::vector<Cords> &v){
		return reinterpret_cast<Figure *>(new Rectangle(v));
	}
};

class Trapezoid_Factory : public Factory{
public:
	Figure *create_figure(){
		return reinterpret_cast<Figure *>(new Trapezoid());
	}
	Figure *create_figure(const Cords &c1, const Cords &c2, const Cords &c3, const Cords &c4){
		return reinterpret_cast<Figure *>(new Trapezoid(c1, c2, c3, c4));
	}
	Figure *create_figure(const std::vector<Cords> &v){
		return reinterpret_cast<Figure *>(new Trapezoid(v));
	}
};

struct command_figure{
	char figure_type;
	std::string cmd;
	Figure *f;
};

class Serializable_Vector{
private:
	Square_Factory *s_factory;
	Rectangle_Factory *r_factory;
	Trapezoid_Factory *t_factory;

	std::vector<Figure *> storage;
	std::fstream file;

	bool file_opened;
	bool vector_saved;

	std::stack<command_figure> undo_commands;

public:
	Serializable_Vector(){
		srand(time(NULL));
		vector_saved = true;
		file_opened = false;
		s_factory = new Square_Factory;
		r_factory = new Rectangle_Factory;
		t_factory = new Trapezoid_Factory;
	}
	~Serializable_Vector(){
		if (file.is_open()){
			file.close();
		}

		clear_storage();
		clear_stack();
		delete s_factory;
		delete r_factory;
		delete t_factory;
	}

	bool open_document(std::string str){
		bool file_exist = check_exist(str);
		while (file_exist){
			std::cout << "Warning! File with name \'" << str << "\' already exists.\n"
					  << "Continuing will cause full data loss\n"
					  << "Continue? (y/n): ";
			char ans;
			std::cin >> ans;
			if (ans != 'y'){
				return false;
			}
		}
		std::ofstream ofs;
		ofs.open(str);

		if (ofs.is_open()){
			ofs.close();
			file.open(str, std::ios::in | std::ios::out | std::ios::binary);
			if (file.is_open()){
				file_opened = true;
				return true;
			}
			else{
				std::cout << "Can not open fstream file\n";
				return false;
			}
		}
		else{
			std::cout << "Can not open ofstream file\n";
			return false;
		}
	}

	void push_begin(Figure *f){
		char type = f->get_figure();
		storage.insert(storage.begin(), f);
		undo_commands.push({type, "pop_begin", nullptr});
		vector_saved = false;
	}

	void pop_begin(){
		if (!storage.empty()){
			Figure *f = storage.front();
			char type = f->get_figure();
			storage.erase(storage.begin());
			undo_commands.push({type, "push_begin", f});
			vector_saved = false;
		}
	}

	void push_end(Figure *f){
		char type = f->get_figure();
		storage.push_back(f);
		undo_commands.push({type, "pop_end", nullptr});
		vector_saved = false;
	}

	void pop_end(){
		if (!storage.empty()){
			Figure *f = storage.back();
			char type = f->get_figure();
			storage.pop_back();
			undo_commands.push({type, "push_end", f});
			vector_saved = false;
		}
	}

	bool export_file(std::string str){

		bool file_exist = check_exist(str);
		if (file_exist){
			std::cout << "Warning! File with name \'" << str << "\' already exists.\n"
					  << "Continuing will cause full data loss\n"
					  << "Continue? (y/n): ";
			char ans;
			std::cin >> ans;
			if (ans != 'y'){
				return false;
			}
		}

		std::ofstream temp;
		temp.open(str);
		temp.close();

		std::fstream file_to_export;
		file_to_export.open(str, std::ios::out | std::ios::binary);

		if (!file_to_export.is_open()){
			std::cout << "Can not open file for export data\n";
			return false;
		}

		size_t storage_size = storage.size();
		file_to_export.write((char *)&storage_size, sizeof(storage.size()));
		for (size_t i = 0; i < storage_size; i++){

			char figure_type = storage[i]->get_figure();
			file_to_export.write((char *)&figure_type, sizeof(figure_type));

			for (size_t j = 0; j < storage[i]->cords.size(); j++){
				file_to_export.write((char *)(&storage[i]->cords[j]), sizeof(Cords));
			}
		}
		file_to_export.close();
		vector_saved = true;
		return true;
	}

	bool import_file(std::string str){
		if (!vector_saved){
			std::cout << "Warning! You have unsaved vector\n"
					  << "Continuing will cause full data loss\n"
					  << "Continue? (y/n): ";

			char ans;
			std::cin >> ans;
			if (ans != 'y'){
				return false;
			}
		}
		clear_storage();
		clear_stack();

		if (file.is_open()){
			file.close();
		}

		file.open(str, std::ios::in | std::ios::out | std::ios::binary);

		if (!file.is_open()){
			std::cout << "Error. Can not import file\n";
			file_opened = false;
			return false;
		}
		else{
			size_t figures_number;
			file.read((char *)&figures_number, sizeof(figures_number));
			for (size_t i = 0; i < figures_number; i++){
				char figure_type;
				file.read((char *)&figure_type, sizeof(figure_type));
				Cords figure_cords[4];
				for (size_t j = 0; j < 4; j++){
					file.read((char *)&figure_cords[j], sizeof(figure_cords[j]));
				}
				switch (figure_type){
				case 's':{
					storage.push_back(s_factory->create_figure(figure_cords[0], figure_cords[1], figure_cords[2], figure_cords[3]));
					break;
				}
				case 'r':{
					storage.push_back(r_factory->create_figure(figure_cords[0], figure_cords[1], figure_cords[2], figure_cords[3]));
					break;
				}
				case 't':{
					storage.push_back(t_factory->create_figure(figure_cords[0], figure_cords[1], figure_cords[2], figure_cords[3]));
					break;
				}
				default:
					std::cout << "Error while reading from import_file file: wrong figure class\n";
					break;
				}
			}
			vector_saved = true;
			file.close();
			file_opened = false;
			return true;
		}
	}

	void undo(){
		if (undo_commands.empty()){
			std::cout << "There is no operations to undo\n";
		}
		else{
			char figure_type = undo_commands.top().figure_type;
			std::string action = undo_commands.top().cmd;

			if (action == "push_begin"){
				if (figure_type == 's'){
					storage.insert(storage.begin(), s_factory->create_figure(undo_commands.top().f->cords));
				}
				else if (figure_type == 'r'){
					storage.insert(storage.begin(), r_factory->create_figure(undo_commands.top().f->cords));
				}
				else if (figure_type == 't'){
					storage.insert(storage.begin(), t_factory->create_figure(undo_commands.top().f->cords));
				}
				else{
					std::cout << "Error while undo: incorrect figure type\n";
				}
				delete undo_commands.top().f;
			}
			else if (action == "pop_begin"){
				if (!storage.empty()){
					delete storage.front();
					storage.erase(storage.begin());
				}
			}
			else if (action == "push_end"){
				if (figure_type == 's'){
					storage.push_back(s_factory->create_figure(undo_commands.top().f->cords));
				}
				else if (figure_type == 'r'){
					storage.push_back(r_factory->create_figure(undo_commands.top().f->cords));
				}
				else if (figure_type == 't'){
					storage.push_back(t_factory->create_figure(undo_commands.top().f->cords));
				}
				else{
					std::cout << "Error while undo: incorrect figure type\n";
				}
				delete undo_commands.top().f;
			}
			else if (action == "pop_end"){
				if (!storage.empty()){
					delete storage.back();
					storage.pop_back();
				}
			}
			else if (action == "clear"){
				clear_storage();
			}
			else{
				std::cout << "Error while undo: wrong action\n";
			}
			undo_commands.pop();
			vector_saved = false;
		}
	}

	bool check_exist(std::string str){
		std::fstream fs;
		fs.open(str);
		if (fs.is_open()){
			fs.close();
			return true;
		}
		else{
			return false;
		}
	}

	void print(){
		for (size_t i = 0; i < storage.size(); i++){
			storage[i]->print();
		}
	}

	size_t size(){
		return storage.size();
	}

	void clear_storage(){
		while (!storage.empty()){
			delete storage.back();
			storage.pop_back();
		}
	}

	void clear_stack(){
		while (!undo_commands.empty()){
			delete undo_commands.top().f;
			undo_commands.pop();
		}
	}

	void generate(unsigned number){
		if (file_opened && !vector_saved){
			std::cout << "Warning! Generating random figures will cause full data loss\n";
			std::cout << "Continue? (y/n): ";
			char ans;
			std::cin >> ans;
			if (ans != 'y'){
				return;
			}
		}
		if (file.is_open()){
			file.close();
		}
		file_opened = false;

		clear_stack();
		clear_storage();

		for (size_t i = 0; i < number; i++){
			std::vector<Cords> svc(4);
			unsigned figure_type = rand() % 3;
			generate_figure(svc, svc.size());
			if (figure_type == 0){
				storage.push_back(s_factory->create_figure(svc));
			}
			else if (figure_type == 1){
				storage.push_back(r_factory->create_figure(svc));
			}
			else{
				storage.push_back(t_factory->create_figure(svc));
			}
		}
		vector_saved = false;
		undo_commands.push({'c', "clear", nullptr});
	}

	void generate_figure(std::vector<Cords> &v, unsigned n){
		if (n == 0){
			return;
		}
		double x0 = static_cast<double>(rand() % 20);
		double y0 = static_cast<double>(rand() % 20);
		double r = static_cast<double>(rand() % 20 + 1);
		for (unsigned i = 0; i < n; i++){
			v[i].x = x0 + r * std::cos(2 * M_PI * i / n);
			v[i].y = y0 + r * std::sin(2 * M_PI * i / n);
		}
	}

	bool is_saved(){
		return vector_saved;
	}
};

void print_actions(){
	std::cout << "Actions:\n";
	std::cout << "[push_begin / push_end]   [square / rectangle / trapezoid]   <cords>\n";
	std::cout << "[pop_begin / pop_end]\n";
	std::cout << "import [filename]\n";
	std::cout << "export [filename]\n";
	std::cout << "generate N\n";
	std::cout << "undo\n";
	std::cout << "exit\n";
}

int main(){
	std::unique_ptr<Square_Factory> square_factory(new Square_Factory);
	std::unique_ptr<Rectangle_Factory> rectangle_factory(new Rectangle_Factory);
	std::unique_ptr<Trapezoid_Factory> trapezoid_factory(new Trapezoid_Factory);

	Serializable_Vector sv;

	print_actions();

	std::string action = "";
	while (action != "exit"){
		std::cout << "\nList:\n";
		sv.print();
		std::cout << "---------------------------------------------\n";
		std::cout << "> ";
		std::cin >> action;

		std::string figure_name;
		std::string file_name;

		if (action == "push_begin" || action == "push_end"){
			std::cin >> figure_name;
			std::vector<Cords> v(4);
			std::cin >> v;

			if (figure_name == "square"){
				if (action == "push_begin"){
					sv.push_begin(square_factory->create_figure(v));
				}
				else{
					sv.push_end(square_factory->create_figure(v));
				}
			}
			else if (figure_name == "rectangle"){
				if (action == "push_begin"){
					sv.push_begin(rectangle_factory->create_figure(v));
				}
				else{
					sv.push_end(rectangle_factory->create_figure(v));
				}
			}
			else if (figure_name == "trapezoid"){
				if (action == "push_begin"){
					sv.push_begin(trapezoid_factory->create_figure(v));
				}
				else{
					sv.push_end(trapezoid_factory->create_figure(v));
				}
			}
			else{
				std::cout << "Error: wrong figure name\n";
			}
		}
		else if (action == "pop_begin"){
			sv.pop_begin();
		}
		else if (action == "pop_end"){
			sv.pop_end();
		}
		else if (action == "import" || action == "export"){
			std::cin >> file_name;
			if (action == "import"){
				sv.import_file(file_name);
			}
			else{
				sv.export_file(file_name);
			}
		}
		else if (action == "undo"){
			sv.undo();
		}
		else if (action == "generate"){
			unsigned n;
			std::cin >> n;
			sv.generate(n);
		}
		else if (action == "exit"){
			if (!sv.is_saved()){
				std::cout << "Warning! Your list is not saved.\n";
				std::cout << "Continue? (y/n): ";
				char ans;
				std::cin >> ans;
				if (ans != 'y'){
					action = "";
				}
			}
		}
		else{
			std::cout << "Wrong command\n";
		}
	}
}
