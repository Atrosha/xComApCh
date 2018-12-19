#pragma once

namespace xComApCh {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Runtime::InteropServices;
	
	
	// GLOBAL VARIABLES AND CONSTANTS
	#define LOC_CASH 0x33D40
	#define LOC_PERS 0x20D6A
	#define LOC_BASE 0x1DF6A
	
	char savegamefile[] = "SAVEGAME.00";
	long int savegamecash;
	char savegametime[40];
	char savegamename[40];
	int numpers = 0;
	int numbase = 0;
	

	struct TBase {
		char buf1[2];
		char Name[19];
		unsigned char Marker;
		unsigned char Structures[8][8];
		char buf2[616];
	};

	struct TPersonal {
		char Name[26];
		short int Index;
		char buf01[7];
		unsigned char Type; // 0 - Agent, 1 - Chemist, 2 - Engineer, 3 - Physic
		char buf2[10];

		unsigned char BSpeed;
		unsigned char BHealth;
		unsigned char BStamina; // divide by 2
		unsigned char BReaction;
		unsigned char BStrength;
		unsigned char BBravery; // multiply by 10
		unsigned char BAccuracy; // 100 - x
		unsigned char BPsiEnergy;
		unsigned char BPsiAttack;
		unsigned char BPsiDefence;

		char buf3[2];

		unsigned char TSpeed;
		unsigned char THealth;
		unsigned char CHealth; // current health - wounded, etc
		char buf4[1];
		unsigned char TStamina; // divide by 2
		unsigned char TReaction;
		unsigned char TStrength;
		unsigned char TBravery; // multiply 10
		unsigned char TPsiEnergy;
		unsigned char TPsiAttack;
		unsigned char TPsiDefence;
		char buf5[1];
		unsigned char TAccuracy; // 100 - x

		char buf6[2];

		unsigned char SkillBiochemist;
		unsigned char SkillPhysic;
		unsigned char SkillEngineer;

		char buf7[129];
	};


	TBase base[8];
	TPersonal pers[180];

		
	/// <summary>
	/// Summary for MainForm
	/// </summary>

	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::NumericUpDown^  numericUpDown1;
	private: System::Windows::Forms::Button^  button3;
	private: System::Windows::Forms::Button^  button4;
	private: System::Windows::Forms::Button^  button5;
	private: System::Windows::Forms::Button^  button6;
	private: System::Windows::Forms::Label^  label8;
	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->numericUpDown1 = (gcnew System::Windows::Forms::NumericUpDown());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->button5 = (gcnew System::Windows::Forms::Button());
			this->button6 = (gcnew System::Windows::Forms::Button());
			this->label8 = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown1))->BeginInit();
			this->SuspendLayout();
			// 
			// textBox1
			// 
			this->textBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 24, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBox1->Location = System::Drawing::Point(12, 12);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(243, 44);
			this->textBox1->TabIndex = 0;
			this->textBox1->Text = L"Hello from 1997!";
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(12, 72);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(171, 23);
			this->button1->TabIndex = 1;
			this->button1->Text = L"Select SaveGame File...";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MainForm::button1_Click);
			// 
			// button2
			// 
			this->button2->Enabled = false;
			this->button2->Location = System::Drawing::Point(12, 101);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(75, 23);
			this->button2->TabIndex = 2;
			this->button2->Text = L"Save";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MainForm::button2_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(5, 220);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(82, 13);
			this->label1->TabIndex = 3;
			this->label1->Text = L"SaveGame File:";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(23, 171);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(64, 13);
			this->label2->TabIndex = 4;
			this->label2->Text = L"Game Time:";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(18, 194);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(69, 13);
			this->label3->TabIndex = 5;
			this->label3->Text = L"Game Name:";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(85, 171);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(0, 13);
			this->label4->TabIndex = 6;
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(85, 194);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(0, 13);
			this->label5->TabIndex = 7;
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Enabled = false;
			this->label6->Location = System::Drawing::Point(85, 220);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(69, 13);
			this->label6->TabIndex = 8;
			this->label6->Text = L"Not Selected";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(57, 248);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(34, 13);
			this->label7->TabIndex = 10;
			this->label7->Text = L"Cash:";
			// 
			// numericUpDown1
			// 
			this->numericUpDown1->Enabled = false;
			this->numericUpDown1->Location = System::Drawing::Point(88, 246);
			this->numericUpDown1->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 2147483647, 0, 0, 0 });
			this->numericUpDown1->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { System::Int32::MinValue, 0, 0, System::Int32::MinValue });
			this->numericUpDown1->Name = L"numericUpDown1";
			this->numericUpDown1->Size = System::Drawing::Size(95, 20);
			this->numericUpDown1->TabIndex = 11;
			this->numericUpDown1->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// button3
			// 
			this->button3->Enabled = false;
			this->button3->Location = System::Drawing::Point(140, 312);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(126, 23);
			this->button3->TabIndex = 12;
			this->button3->Text = L"Maximize Personal";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &MainForm::button3_Click);
			// 
			// button4
			// 
			this->button4->Location = System::Drawing::Point(0, 0);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(75, 23);
			this->button4->TabIndex = 0;
			// 
			// button5
			// 
			this->button5->Enabled = false;
			this->button5->Location = System::Drawing::Point(140, 283);
			this->button5->Name = L"button5";
			this->button5->Size = System::Drawing::Size(126, 23);
			this->button5->TabIndex = 14;
			this->button5->Text = L"Cure All Personal";
			this->button5->UseVisualStyleBackColor = true;
			this->button5->Click += gcnew System::EventHandler(this, &MainForm::button5_Click);
			// 
			// button6
			// 
			this->button6->Enabled = false;
			this->button6->Location = System::Drawing::Point(8, 283);
			this->button6->Name = L"button6";
			this->button6->Size = System::Drawing::Size(126, 23);
			this->button6->TabIndex = 15;
			this->button6->Text = L"Maximize Bases";
			this->button6->UseVisualStyleBackColor = true;
			this->button6->Click += gcnew System::EventHandler(this, &MainForm::button6_Click);
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label8->Location = System::Drawing::Point(64, 377);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(203, 13);
			this->label8->TabIndex = 16;
			this->label8->Text = L"Copyright by Vasiliy \"Atrosha\" Panasenko";
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(274, 399);
			this->Controls->Add(this->label8);
			this->Controls->Add(this->button6);
			this->Controls->Add(this->button5);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->numericUpDown1);
			this->Controls->Add(this->label7);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->textBox1);
			this->Name = L"MainForm";
			this->Text = L"X-COM Apocalypse Cheat";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	void String2Char(System::String ^ str, char * ch) {
		char* chars;

		chars = (char*)(void*)Marshal::StringToHGlobalAnsi(str);
		strcpy(ch, chars);
		Marshal::FreeHGlobal(IntPtr((void *)chars));
	}

	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {

		OpenFileDialog^ openFileDialog1 = gcnew OpenFileDialog;
		// openFileDialog1->InitialDirectory = "C:\\";
		openFileDialog1->Filter = "SaveGame files (SAVEGAME.*)|SAVEGAME.*|All files (*.*)|*.*";
		openFileDialog1->FilterIndex = 1;
		openFileDialog1->RestoreDirectory = true;

		if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			label6->Text = openFileDialog1->SafeFileName;
			label6->Enabled = true;
			String2Char(openFileDialog1->FileName, savegamefile);

			FILE *datafile;

			if ((datafile = fopen(savegamefile, "rb")) != NULL) { // file opens?
				fseek(datafile, 0, SEEK_SET);
				fread(&savegametime, sizeof(savegametime), 1, datafile);
				fread(&savegamename, sizeof(savegamename), 1, datafile);

				label4->Text = gcnew String(savegametime);
				label5->Text = gcnew String(savegamename);

				fseek(datafile, LOC_CASH, SEEK_SET);
				fread(&savegamecash, sizeof(savegamecash), 1, datafile);
				numericUpDown1->Value = savegamecash;

				fseek(datafile, LOC_BASE, SEEK_SET);
				for (int i = 0; i < 8; i++) {
					fread(&base[i], sizeof(TBase), 1, datafile);
					if (base[i].Marker > 0) { numbase++; };
				};

				fseek(datafile, LOC_PERS, SEEK_SET);
				for (int i = 0; i < 180; i++) {
					fread(&pers[i], sizeof(TPersonal), 1, datafile);
					if (pers[i].Index > 0) { numpers++; };
				};

				numericUpDown1->Enabled = true;
				button2->Enabled = true;

				if (numbase > 0) {
					button6->Enabled = true;
				}
				else MessageBox::Show("No Bases (Maybe error occured)", "Information", MessageBoxButtons::OK, MessageBoxIcon::Information);

				if (numpers > 0) {
					button3->Enabled = true;
					button5->Enabled = true;
				}
				else MessageBox::Show("No personal (Agents, Scientists, Engineers)", "Information", MessageBoxButtons::OK, MessageBoxIcon::Information);
			}
			else MessageBox::Show("Error occurs while opening savegame file!", "Error", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
			fclose(datafile);

		} else MessageBox::Show("Select savegame file!", "Error", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
		
	}
	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {

		FILE *datafile;
		
		if ((datafile = fopen(savegamefile, "r+b")) != NULL) { // file opens?
			fseek(datafile, LOC_CASH, SEEK_SET);
			savegamecash = Convert::ToInt32(numericUpDown1->Value);
			fwrite(&savegamecash, sizeof(savegamecash), 1, datafile);
			fseek(datafile, LOC_PERS, SEEK_SET);
			for (int i = 0; i < 180; i++) {
				fwrite(&pers[i], sizeof(TPersonal), 1, datafile);
			};
			fseek(datafile, LOC_BASE, SEEK_SET);
			for (int i = 0; i < 8; i++) {
				fwrite(&base[i], sizeof(TBase), 1, datafile);
			};
		}
		else MessageBox::Show("Error occurs while opening savegame file!", "Error", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
	
		fclose(datafile);

		MessageBox::Show("Changes Saved to File", "Information", MessageBoxButtons::OK, MessageBoxIcon::Information);
	}
	private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) {
		for (int i = 0; i <= numpers; i++) {
			switch (pers[i].Type) {
			case 0:
				pers[i].TSpeed = 100;
				pers[i].THealth = 100;
				pers[i].CHealth = pers[i].THealth;
				pers[i].TStamina = 200;
				pers[i].TReaction = 100;
				pers[i].TStrength = 100;
				pers[i].TBravery = 10;
				if (pers[i].BPsiEnergy > 0) { pers[i].TPsiEnergy = 100; };
				if (pers[i].BPsiAttack > 0) { pers[i].TPsiAttack = 100; };
				pers[i].TPsiDefence = 100;
				pers[i].TAccuracy = 0;
				break;
			case 1:
				pers[i].SkillBiochemist = 255;
				break;
			case 2:
				pers[i].SkillEngineer = 255;
				break;
			case 3:
				pers[i].SkillPhysic = 255;
				break;
			};
		};
		button3->Enabled = false;
		button5->Enabled = false;
	}
	private: System::Void button5_Click(System::Object^  sender, System::EventArgs^  e) {
		for (int i = 0; i <= numpers; i++) { pers[i].CHealth = pers[i].THealth; };
		button5->Enabled = false;
	}
	private: System::Void button6_Click(System::Object^  sender, System::EventArgs^  e) {
		for (int c = 0; c < numbase; c++) {
			for (int y = 1; y < 7; y++) {
				for (int x = 1; x < 7; x++) {
					if (base[c].Structures[y][x] < 15) { base[c].Structures[y][x] = 15; };
				};
			};
			for (int x = 1; x < 7; x++) {
				if (base[c].Structures[0][x] < 16) { base[c].Structures[0][x] = 14; };
				if (base[c].Structures[7][x] < 16) { base[c].Structures[7][x] = 11; };
			};
			for (int y = 1; y < 7; y++) {
				if (base[c].Structures[y][0] < 16) { base[c].Structures[y][0] = 7; };
				if (base[c].Structures[y][7] < 16) { base[c].Structures[y][7] = 13; };
			};

			if (base[c].Structures[0][0] < 16) { base[c].Structures[0][0] = 6; };
			if (base[c].Structures[0][7] < 16) { base[c].Structures[0][7] = 12; };
			if (base[c].Structures[7][0] < 16) { base[c].Structures[7][0] = 3; };
			if (base[c].Structures[7][7] < 16) { base[c].Structures[7][7] = 9; };

			button6->Enabled = false;
		};
	}
};
}
