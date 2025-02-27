#include "borrowClass.h"
#include <iostream>
using namespace std;

borrowClass::borrowClass(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	init();
	
}

borrowClass::~borrowClass()
{}
string borrowClass::readFileIntoString(const string& path) {
	auto ss = ostringstream{};
	ifstream input_file(path);
	if (!input_file.is_open()) {
		cerr << "Could not" << endl;
		exit(EXIT_FAILURE);
	}
	ss << input_file.rdbuf();
	return ss.str();
}
void borrowClass::init() {

	string filename("C:\\Users\\KOSTA\\Desktop\\book_info\\book_info\\book_info.csv");
	string file_contents;
	char delimiter = ',';

	file_contents = readFileIntoString(filename);

	istringstream sstream(file_contents);
	string record;
	string book_info[15][5];
	int i = 0;
	int j = 0;
	while (std::getline(sstream, record)) {
		istringstream line(record);
		while (std::getline(line, record, delimiter)) {
			book_info[i][j] = record;
			j++;
			if (j > 4) {
				j = 0;
				i++;
			}
		}
	}
	for (int i = 0; i < 15; i++) {
			ui.tableWidget->insertRow(ui.tableWidget->rowCount());
			ui.tableWidget->setItem(ui.tableWidget->rowCount() - 1, 0, new QTableWidgetItem(QString::fromLocal8Bit(book_info[i][0])));
			ui.tableWidget->setItem(ui.tableWidget->rowCount() - 1, 1, new QTableWidgetItem(QString::fromLocal8Bit(book_info[i][1])));
			ui.tableWidget->setItem(ui.tableWidget->rowCount() - 1, 2, new QTableWidgetItem(QString::fromLocal8Bit(book_info[i][2])));
	}
	ui.tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
}
void borrowClass::show_book_info() {
	int row = ui.tableWidget->currentRow();
	booki = new bookinfoClass(this);
	booki->show();
}
void borrowClass::search_book() {
	QList<QTableWidgetItem*> searchItem;

	if (ui.lineEdit->text().isEmpty()) {
		for (int i = 0; i < ui.tableWidget->rowCount(); i++) {
			if (ui.tableWidget->isRowHidden(i)) {
				ui.tableWidget->showRow(i);
			}
		}
		return;
	}
	searchItem = ui.tableWidget->findItems(ui.lineEdit->text(), Qt::MatchExactly | Qt::MatchRecursive);
	//searchItem = ui.tableWidget->findItems(ui.lineEdit->text(), Qt::MatchContains | Qt::MatchRecursive);

	if (searchItem.count() > 0) {
		for (int i = 0; i < ui.tableWidget->rowCount(); i++) {
			ui.tableWidget->hideRow(i);
		}
		for (int i = 0; i < searchItem.count(); i++) {
			ui.tableWidget->showRow(searchItem.at(i)->row());
		}
	}
	else {
		for (int i = 0; i < ui.tableWidget->rowCount(); i++) {
			ui.tableWidget->hideRow(i);
		}
	}
	
}