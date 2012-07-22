#ifndef FLOW_H
#define FLOW_H

#include "ui_Flow.h"

nm_value Culc_Ras(const nm_value & x);

#include <QFile>



///Диалог, предназначенный для выполнения расчетов газа при истечении через сопло.

/**
*/

class Flow: public QWidget
{
	Q_OBJECT
public:
	Flow(QWidget *parent=0);														///<Конструктор.
	~Flow();																						///<Деструктор.

public:
	QFile * out_file;																		///<Файл для вывода результатов расчета.
/**<Данный файл создается в текущем каталоге (откуда был произведен запуск программы).
Результаты расчета в него попадают при нажатии на кнопку рассчитать.
*/
public slots:
	void reculc_Form(nm_value tmp); 										///<Выполнение пересчета по данным формы.
private:
	Ui::Flow ui;																				///<Диалог.

	static nm_value P_in;																///<Давление перед соплом.
	static nm_value P_out;															///<Давление за соплом.
	static nm_value ro_in;															///<Плотность перед соплом.
	static nm_value ro_out;															///<Плотность за соплом.
	static nm_value dP;																	///<Перепад давлеия на сопле.
	static nm_value R_mu;																///<Универсальная газовая постоянная.
	static nm_value T_in;																///<Температура газа перед соплом.
	static nm_value T_out;															///<Температура газа за соплом.
	static nm_value mu;																	///<Молекулярная масса газа, проходящего через сопло.
	static nm_value F;																	///<Геометрическая площадь сопла.
	static nm_value W;																	///<Скорость.
	static nm_value G;																	///<Массовый расход.
	static nm_value G_kr;																	///<Массовый расход.
	static nm_value Pout_kr;
	static nm_value k;																	///<Коэффициент адиабаты газа, проходящего через сопло.
	
friend	nm_value Culc_Ras(const nm_value & x);	
	void dbg_print();
private slots:
	void on_pB_Print_pressed(); 												///<Вывод данных расчета на консоль и в файл.
	void on_pB_Culculate_pressed();											///<Рассчитать расход через сопло.
	void on_eBox_dP_valueChanged(nm_value aVal);
	void on_eBox_P_out_valueChanged(nm_value aVal);
	void on_eBox_P_in_valueChanged(nm_value aVal);
};

#endif // FLOW_H
