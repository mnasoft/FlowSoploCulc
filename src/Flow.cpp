#include "Flow.h"
#include "Flow.moc"
#include "math.h"
#include "method_half_div.h"

/**Инициализация статических переменных класса Flow::*/
nm_value Flow::P_in;		///<Давление перед соплом.
nm_value Flow::P_out;		///<Давление за соплом.
nm_value Flow::ro_in;		///<Плотность перед соплом.
nm_value Flow::ro_out;	///<Плотность за соплом.
nm_value Flow::dP;			///<Перепад давлеия на сопле.
nm_value Flow::R_mu;		///<Универсальная газовая постоянная.
nm_value Flow::T_in;		///<Температура газа перед соплом.
nm_value Flow::T_out;		///<Температура газа за соплом.
nm_value Flow::mu;			///<Молекулярная масса газа, проходящего через сопло.
nm_value Flow::F;				///<Геометрическая площадь сопла.
nm_value Flow::W; 			///<Скорость.
nm_value Flow::G; 			///<Массовый расход.
nm_value Flow::G_kr;
nm_value Flow::Pout_kr;
nm_value Flow::k;				///<Коэффициент адиабаты газа, проходящего через сопло.


void Flow::dbg_print()
{
	QTextStream out (stdout);
	out << "----------------------------------------------------------------" << endl;
	out << ui.eBox_P_in->outValue() << endl;
	out << ui.eBox_T_in->outValue() << endl;
	out << "Ro_in  = " << Flow::ro_in << endl;

	out << ui.eBox_P_out->outValue() << endl;
	out << ui.eBox_T_out->outValue() << endl;
	out << "Ro_out = " << Flow::ro_in << endl;

	out << ui.eBox_dP->outValue() << endl;

	out << ui.eBox_mu->outValue() << endl;

	out
	<<	ui.eBox_k->getDescription() << "= "
	<<	ui.eBox_k->getValue() << " "
	<<	ui.eBox_k->getValueDimension() << endl;

	out << ui.eBox_G->outValue() << endl;
	out << ui.eBox_F->outValue() << endl;

	out << ui.eBox_W->outValue() << endl;
	out << ui.eBox_W_kritikal->outValue() << endl;

/****************************************************************/
	QTextStream out_txt_stream(out_file);
	out_txt_stream << "----------------------------------------------------------------" << endl;

	out_txt_stream << ui.eBox_P_in->outValue() << endl;
	out_txt_stream << ui.eBox_T_in->outValue() << endl;
	out_txt_stream << "Ro_in  = " << Flow::ro_in << endl;

	out_txt_stream << ui.eBox_P_out->outValue() << endl;
	out_txt_stream << ui.eBox_T_out->outValue() << endl;
	out_txt_stream << "Ro_out = " << Flow::ro_in << endl;

	out_txt_stream << ui.eBox_dP->outValue() << endl;

	out_txt_stream << ui.eBox_mu->outValue() << endl;

	out_txt_stream
	<<	ui.eBox_k->getDescription() << "= "
	<<	ui.eBox_k->getValue() << " "
	<<	ui.eBox_k->getValueDimension() << endl;

	out_txt_stream << ui.eBox_G->outValue() << endl;
	out_txt_stream << ui.eBox_F->outValue() << endl;

	out_txt_stream << ui.eBox_W->outValue() << endl;
	out_txt_stream << ui.eBox_W_kritikal->outValue() << endl;
}

Flow::Flow(QWidget *parent)
    : QWidget(parent), out_file(0)
{
	out_file=new QFile("FlowSoploCulc_out.txt");

	if (!out_file->open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
		return;
	
	ui.setupUi(this);

	ui.eBox_P_in->setExpansion(2);
	ui.eBox_P_in->setDescription(QString::fromUtf8("P_in   "));
	ui.eBox_P_in->setVal(nm_value(2.0e5,QString::fromUtf8("Pa")));
	ui.eBox_P_in->setValueType(EnterBox::str_pressure);
	ui.eBox_P_in->setValueDimension(QString::fromUtf8("Pa"));

	ui.eBox_P_out->setExpansion(2);
	ui.eBox_P_out->setDescription(QString::fromUtf8("P_out  "));
	ui.eBox_P_out->setVal(nm_value(1.0e5,QString::fromUtf8("Pa")));
	ui.eBox_P_out->setValueType(EnterBox::str_pressure);
	ui.eBox_P_out->setValueDimension(QString::fromUtf8("Pa"));
	
	ui.eBox_dP->setExpansion(2);
	ui.eBox_dP->setDescription(QString::fromUtf8("dP     "));
	ui.eBox_dP->setVal(nm_value(1.0e5,QString::fromUtf8("Pa")));
	ui.eBox_dP->setValueType(EnterBox::str_pressure);
	ui.eBox_dP->setValueDimension(QString::fromUtf8("Pa"));
	
	ui.eBox_P_in->setLockValueChangedSignal(false);
	ui.eBox_P_out->setLockValueChangedSignal(false);
	ui.eBox_dP->setLockValueChangedSignal(false);

	ui.eBox_T_in->setExpansion(2);
	ui.eBox_T_in->setDescription(QString::fromUtf8("T_in   "));
	ui.eBox_T_in->setVal(nm_value(273.0+15.0,QString::fromUtf8("K")));
	ui.eBox_T_in->setValueDimension(QString::fromUtf8("K"));

	ui.eBox_T_out->setExpansion(2);
	ui.eBox_T_out->setDescription(QString::fromUtf8("T_out  "));
	ui.eBox_T_out->setVal(nm_value(273.0+14.0,QString::fromUtf8("K")));
	ui.eBox_T_out->setValueDimension(QString::fromUtf8("K"));

	ui.eBox_mu->setExpansion(2);
	ui.eBox_mu->setDescription(QString::fromUtf8("mu     "));
	ui.eBox_mu->setVal(nm_value(0.029,QString::fromUtf8("kg/mol")));
	ui.eBox_mu->setValueDimension(QString::fromUtf8("kg/mol"));
	
	
	ui.eBox_F->setExpansion(2);
	ui.eBox_F->setDescription(QString::fromUtf8("F      "));
	ui.eBox_F->setVal(nm_value(30.00,QString::fromUtf8("mm2")));
	ui.eBox_F->setValueDimension(QString::fromUtf8("mm2"));
	
	ui.eBox_W->setExpansion(2);
	ui.eBox_W->setDescription(QString::fromUtf8("W      "));
	ui.eBox_W->setVal(nm_value(250.0,QString::fromUtf8("m/s")));
	ui.eBox_W->setValueDimension(QString::fromUtf8("m/s"));
	
	ui.eBox_G->setExpansion(2);
	ui.eBox_G->setDescription(QString::fromUtf8("G      "));
	ui.eBox_G->setVal(nm_value(0.0125,QString::fromUtf8("kg/s")));
	ui.eBox_G->setValueDimension(QString::fromUtf8("kg/s"));
	
	
	ui.eBox_W_kritikal->setExpansion(2);
	ui.eBox_W_kritikal->setDescription(QString::fromUtf8("W_kr   "));
	ui.eBox_W_kritikal->setVal(nm_value(330.0,QString::fromUtf8("m/s")));
	ui.eBox_W_kritikal->setValueDimension(QString::fromUtf8("m/s"));
	

	ui.eBox_k->setExpansion(2);
	ui.eBox_k->setDescription(QString::fromUtf8("k      "));
	ui.eBox_k->setVal(nm_value(1.40,QString::fromUtf8("")));
	ui.eBox_k->setValueDimension(QString::fromUtf8(""));
	
	ui.eBox_Gkr->setExpansion(2);
	ui.eBox_Gkr->setDescription(QString::fromUtf8("G_kr"));
	ui.eBox_Gkr->setVal(nm_value(0.0,QString::fromUtf8("kg/s")));
	ui.eBox_Gkr->setValueDimension(QString::fromUtf8("kg/s"));

	ui.eBox_Pout_kr->setExpansion(2);
	ui.eBox_Pout_kr->setDescription(QString::fromUtf8("Pout_kr"));
	ui.eBox_Pout_kr->setVal(nm_value(0.0,QString::fromUtf8("Pa")));
	ui.eBox_Pout_kr->setValueType(EnterBox::str_pressure);
	ui.eBox_Pout_kr->setValueDimension(QString::fromUtf8("Pa"));

	
	ui.rB_Area->setChecked (true);
}

	Flow::~Flow()
{
	out_file->close();
	delete out_file;
}


void Flow::reculc_Form(nm_value tmp)
{
	QTextStream out (stdout);
	out <<"reculs_Form()"<<endl;
	out << tmp <<endl;


	return;
}

void Flow::on_eBox_P_in_valueChanged(nm_value aVal)
{
	QTextStream out (stdout);
	out <<"on_eBox_P_in_valueChanged(" << aVal<< ")"<<endl;

	P_in	=ui.eBox_P_in->getVal();
	P_out	=ui.eBox_P_out->getVal();
	dP	=ui.eBox_dP->getVal();

	out 
		<<"P_in  = "<< P_in 
		<<"P_out = "<< P_out
		<<"dP    = "<< dP 
		<< endl;
	dP	= P_in - P_out;

	out 
		<<"P_in  = "<< P_in
		<<"P_out = "<< P_out
		<<"dP    = "<< dP
		<< endl;

	ui.eBox_P_in->setVal(P_in);
	ui.eBox_P_out->setVal(P_out);
	ui.eBox_dP->setVal(dP);

	return;
}

void Flow::on_eBox_P_out_valueChanged(nm_value aVal)
{
	QTextStream out (stdout);
	out <<"on_eBox_P_out_valueChanged(" << aVal<< ")"<<endl;
	P_in	=ui.eBox_P_in->getVal();
	P_out	=ui.eBox_P_out->getVal();
	dP	=ui.eBox_dP->getVal();

	out 
		<<"P_in  = "<< P_in 
		<<"P_out = "<< P_out
		<<"dP    = "<< dP 
		<< endl;
	dP	= P_in - P_out;

	out 
		<<"P_in  = "<< P_in
		<<"P_out = "<< P_out
		<<"dP    = "<< dP
		<< endl;

	ui.eBox_P_in->setVal(P_in);
	ui.eBox_P_out->setVal(P_out);
	ui.eBox_dP->setVal(dP);
	return;
}

void Flow::on_eBox_dP_valueChanged(nm_value aVal)
{
	QTextStream out (stdout);
	out <<"on_eBox_dP_valueChanged(" << aVal<< ")"<<endl;
	P_in	=ui.eBox_P_in->getVal();
	P_out	=ui.eBox_P_out->getVal();
	dP	=ui.eBox_dP->getVal();

	out 
		<<"P_in  = "<< P_in 
		<<"P_out = "<< P_out
		<<"dP    = "<< dP 
		<< endl;
	P_in	= P_out + dP ;

	out 
		<<"P_in  = "<< P_in
		<<"P_out = "<< P_out
		<<"dP    = "<< dP
		<< endl;

	ui.eBox_P_in->setVal(P_in);
	ui.eBox_P_out->setVal(P_out);
	ui.eBox_dP->setVal(dP);
	return;
}

void Flow::on_pB_Culculate_pressed()
{
	R_mu = nm_value::get_Pa()*nm_value::get_kg()/nm_value::get_mol()*8.314 / (nm_value::get_kg()/nm_value::get_m().pownm(3)*nm_value::get_K());
	T_in=ui.eBox_T_in->getVal();
	T_out=ui.eBox_T_out->getVal();
	mu=ui.eBox_mu->getVal();
	F=ui.eBox_F->getVal();		ui.eBox_F->setVal(F);//Площадь
	W=ui.eBox_W->getVal();		ui.eBox_W->setVal(W); //Скорость
	G=ui.eBox_G->getVal();		ui.eBox_G->setVal(G);//Расход
	G_kr=ui.eBox_Gkr->getVal();	ui.eBox_Gkr->setVal(G_kr);
	Pout_kr=ui.eBox_Pout_kr->getVal();	ui.eBox_Pout_kr->setVal(Pout_kr);
	k=ui.eBox_k->getVal();		ui.eBox_k->setVal(k);
	P_in = ui.eBox_P_in->getVal();
	P_out = ui.eBox_P_out->getVal();
	
	ro_in = P_in * mu / (T_in * R_mu);
	ro_out = P_out * mu / (T_in * R_mu);
	
	nm_value W_kritikal=ui.eBox_W_kritikal->getVal();
	
	if (ui.rB_Area->isChecked())
	{
		T_out=T_in*(P_out/P_in).pown(((k-1)/k).toDouble());
		ui.eBox_T_out->setVal(T_out);
		/**************************************************************************************************/
		W_kritikal=(k*2.0)/(k+1.0);
		W_kritikal=W_kritikal*P_in/ro_in;
		W_kritikal = W_kritikal.pownm2 (1 , 2);
		ui.eBox_W_kritikal->setVal(W_kritikal);
		/**************************************************************************************************/
		W = (k * 2)/(k - 1) * P_in / ro_in;
		W = W *( -(P_out/P_in).pown( ((k-1)/k).toDouble() ) + 1 );
		W = W.pownm2 (1 , 2);
		ui.eBox_W->setVal(W);
		/**************************************************************************************************/
		F = (k*2.0)/(k-1.0)*ro_in*P_in;
		nm_value p1=(P_out/P_in).pown(2.0/k.toDouble());
		nm_value p2=(P_out/P_in).pown(((k+1)/k).toDouble());
		F = F * ( p1 - p2 );
		F = F.pownm2 (1 , 2);
		F = G/F;
		ui.eBox_F->setVal(F);
		/**************************************************************************************************/
		return;
	}
	if (ui.rB_Flow->isChecked())
	{
		W_kritikal=(k*2.0)/(k+1.0);
		W_kritikal=W_kritikal*R_mu/mu*T_in;
		W_kritikal = W_kritikal.pownm2 (1 , 2);
		ui.eBox_W_kritikal->setVal(W_kritikal);
		/**************************************************************************************************/
		T_out=T_in*(P_out/P_in).pown(((k-1)/k).toDouble());
		ui.eBox_T_out->setVal(T_out);
		/**************************************************************************************************/
		G = (k*2.0)/(k-1.0)*ro_in*P_in;
		nm_value p1=(P_out/P_in).pown(2.0/k.toDouble());
		nm_value p2=(P_out/P_in).pown(((k+1)/k).toDouble());
		G = G * ( p1 - p2 );
		G = F * G.pownm2 (1 , 2);
		ui.eBox_G->setVal(G);
		/**************************************************************************************************/
		G_kr =(k*2.0)/(k+1.0)*ro_in*P_in;
		G_kr = G_kr.pownm2 (1 , 2);
		G_kr = G_kr * F * (nm_value(2.0)/(k+1)).pown(1/(k-1).toDouble());
		ui.eBox_Gkr->setVal(G_kr);
		/**************************************************************************************************/
		Pout_kr=P_in*(nm_value(2.0)/(k+1)).pown((k/(k-1)).toDouble());
		ui.eBox_Pout_kr->setVal(Pout_kr);
		/**************************************************************************************************/
		W = (k * 2)/(k - 1) * P_in / ro_in;
		W = W *( -(P_out/P_in).pown( ((k-1)/k).toDouble() ) + 1 );
		W = W.pownm2 (1 , 2);
		ui.eBox_W->setVal(W);
		return;
	}
	if (ui.rB_Pin_by_velocity->isChecked())
	{
		nm_value tmp = (k * 2) / (k - 1) * R_mu / mu * T_in;
		tmp = -W*W/tmp + 1;
		tmp = tmp.pown((k/(k-1)).toDouble());
		P_in= P_out/tmp;
		ui.eBox_P_in->setVal(P_in);
		/**************************************************************************************************/
		T_out=T_in*(P_out/P_in).pown(((k-1)/k).toDouble());
		ui.eBox_T_out->setVal(T_out);
		/**************************************************************************************************/
		W_kritikal=(k*2.0)/(k+1.0);
		W_kritikal=W_kritikal*R_mu/mu*T_in;
		W_kritikal = W_kritikal.pownm2 (1 , 2);
		ui.eBox_W_kritikal->setVal(W_kritikal);
		/**************************************************************************************************/
		G = (k*2.0)/(k-1.0)*ro_in*P_in;
		nm_value p1=(P_out/P_in).pown(2.0/k.toDouble());
		nm_value p2=(P_out/P_in).pown(((k+1)/k).toDouble());
		G = G * ( p1 - p2 );
		G = F * G.pownm2 (1 , 2);
		ui.eBox_G->setVal(G);
		/**************************************************************************************************/
		return;
	}
	if (ui.rB_Pin_by_flow->isChecked())
	{
		P_in = Half_Div(P_out + nm_value(0.01, "Pa"), P_out*10000.0, nm_value(0.01, "Pa"), Culc_Ras);
		ui.eBox_P_in->setVal(P_in);
		/**************************************************************************************************/
		W_kritikal=(k*2.0)/(k+1.0);
		W_kritikal=W_kritikal*R_mu/mu*T_in;
		W_kritikal = W_kritikal.pownm2 (1 , 2);
		ui.eBox_W_kritikal->setVal(W_kritikal);
		/**************************************************************************************************/
		W = (k * 2)/(k - 1) * P_in / ro_in;
		W = W *( -(P_out/P_in).pown( ((k-1)/k).toDouble() ) + 1 );
		W = W.pownm2 (1 , 2);
		ui.eBox_W->setVal(W);
		/**************************************************************************************************/
		return;
	}
	return;
}

nm_value Culc_Ras(const nm_value & x)
{
	Flow::P_in=x;
	nm_value G_rez;
	
	Flow::ro_in = Flow::P_in * Flow::mu / (Flow::T_in * Flow::R_mu);
	
	G_rez = (Flow::k*2.0)/(Flow::k-1.0)*Flow::ro_in*Flow::P_in;
	
	nm_value p1=(Flow::P_out/Flow::P_in).pown(2.0/Flow::k.toDouble());
	nm_value p2=(Flow::P_out/Flow::P_in).pown(((Flow::k+1)/Flow::k).toDouble());
	G_rez = G_rez * ( p1 - p2 );
	G_rez = Flow::F * G_rez.pownm2 (1 , 2) - Flow::G;

	return G_rez ;
}


void Flow::on_pB_Print_pressed()
{
	dbg_print();

}
