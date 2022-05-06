#pragma once

namespace Obserwacje {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace MySql::Data::MySqlClient;
	public ref class Program : public System::Windows::Forms::Form
	{
	public:
		String^ konfiguracja = L"datasource=localhost;port=3306;username=root;password=YES;database=relacja";
		int id_uzytkownika;
		Program(int uzytkownik)
		{
			InitializeComponent();
			id_uzytkownika = uzytkownik;	
		}
	protected:
		~Program()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ btnPSzukaj;
	public:
	private: System::Windows::Forms::TextBox^ txtPSzukaj;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::DataGridView^ dgUzytkownicy;
	private: System::Windows::Forms::TabControl^ tabControl1;
	protected:
	private: System::Windows::Forms::TabPage^ tabPage2;
	private:
		System::ComponentModel::Container^ components;
#pragma region Windows Form Designer generated code	
		void InitializeComponent(void)
		{
			this->tabControl1 = (gcnew System::Windows::Forms::TabControl());
			this->tabPage2 = (gcnew System::Windows::Forms::TabPage());
			this->btnPSzukaj = (gcnew System::Windows::Forms::Button());
			this->txtPSzukaj = (gcnew System::Windows::Forms::TextBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->dgUzytkownicy = (gcnew System::Windows::Forms::DataGridView());
			this->tabControl1->SuspendLayout();
			this->tabPage2->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgUzytkownicy))->BeginInit();
			this->SuspendLayout();
			this->tabControl1->Alignment = System::Windows::Forms::TabAlignment::Bottom;
			this->tabControl1->Controls->Add(this->tabPage2);
			this->tabControl1->Location = System::Drawing::Point(12, 12);
			this->tabControl1->Multiline = true;
			this->tabControl1->Name = L"tabControl1";
			this->tabControl1->SelectedIndex = 0;
			this->tabControl1->Size = System::Drawing::Size(1095, 606);
			this->tabControl1->TabIndex = 0;
			this->tabPage2->Controls->Add(this->btnPSzukaj);
			this->tabPage2->Controls->Add(this->txtPSzukaj);
			this->tabPage2->Controls->Add(this->label4);
			this->tabPage2->Controls->Add(this->dgUzytkownicy);
			this->tabPage2->Location = System::Drawing::Point(4, 4);
			this->tabPage2->Name = L"tabPage2";
			this->tabPage2->Padding = System::Windows::Forms::Padding(3);
			this->tabPage2->Size = System::Drawing::Size(1087, 580);
			this->tabPage2->TabIndex = 1;
			this->tabPage2->Text = L"U¿ytkownicy";
			this->tabPage2->UseVisualStyleBackColor = true;
			this->tabPage2->Click += gcnew System::EventHandler(this, &Program::tabPage2_Click);
			this->btnPSzukaj->Location = System::Drawing::Point(283, 4);
			this->btnPSzukaj->Name = L"btnPSzukaj";
			this->btnPSzukaj->Size = System::Drawing::Size(75, 23);
			this->btnPSzukaj->TabIndex = 3;
			this->btnPSzukaj->Text = L"szukaj";
			this->btnPSzukaj->UseVisualStyleBackColor = true;
			this->btnPSzukaj->Click += gcnew System::EventHandler(this, &Program::btnPSzukaj_Click);
			this->txtPSzukaj->Location = System::Drawing::Point(81, 6);
			this->txtPSzukaj->Name = L"txtPSzukaj";
			this->txtPSzukaj->Size = System::Drawing::Size(196, 20);
			this->txtPSzukaj->TabIndex = 2;
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(9, 9);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(67, 13);
			this->label4->TabIndex = 1;
			this->label4->Text = L"U¿ytkownicy";
			this->dgUzytkownicy->AllowUserToOrderColumns = true;
			this->dgUzytkownicy->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dgUzytkownicy->Location = System::Drawing::Point(6, 44);
			this->dgUzytkownicy->Name = L"dgUzytkownicy";
			this->dgUzytkownicy->Size = System::Drawing::Size(1075, 258);
			this->dgUzytkownicy->TabIndex = 0;
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1111, 617);
			this->Controls->Add(this->tabControl1);
			this->Name = L"Program";
			this->Text = L"Program";
			this->Load += gcnew System::EventHandler(this, &Program::Program_Load);
			this->tabControl1->ResumeLayout(false);
			this->tabPage2->ResumeLayout(false);
			this->tabPage2->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgUzytkownicy))->EndInit();
			this->ResumeLayout(false);
		}

#pragma endregion
	private: System::Void Program_Load(System::Object^ sender, System::EventArgs^ e) {
	}
//wyszukiwanie uzytkownikow
	private: System::Void btnPSzukaj_Click(System::Object^ sender, System::EventArgs^ e) {
		MySqlConnection^ laczBaze = gcnew MySqlConnection(konfiguracja);
		MySqlCommand^ zapytanie = gcnew MySqlCommand("SELECT id_uzytkownika, imie, nazwisko, email AS login, uprawnienia_dostepu FROM kartoteka_uzytkownikow WHERE CONCAT(imie, ' ', nazwisko, email) LIKE '%" + txtPSzukaj->Text + "%' ORDER BY nazwisko;", laczBaze);
		try {
			laczBaze->Open();
			MySqlDataAdapter^ moja = gcnew MySqlDataAdapter();
			moja->SelectCommand = zapytanie;
			DataTable^ tabela = gcnew DataTable();
			moja->Fill(tabela);

			BindingSource^ zrodlo = gcnew BindingSource();
			zrodlo->DataSource = tabela;
			dgUzytkownicy->DataSource = zrodlo;
		}
		catch (Exception^ komunikat) {
			MessageBox::Show(komunikat->Message);
		}
		dgUzytkownicy->Columns[0]->Visible = false;
	}
	private: System::Void tabPage2_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	};
}