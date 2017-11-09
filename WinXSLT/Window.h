#pragma once
	
#include <xalanc/Include/PlatformDefinitions.hpp>
#include <xercesc/util/PlatformUtils.hpp>
#include <xalanc/XalanTransformer/XalanTransformer.hpp>


namespace WinXSLT {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Runtime::InteropServices;

	
	public ref class Window : public System::Windows::Forms::Form
	{
	public:
		Window(void)
		{
			InitializeComponent();
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Window()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
    private: System::Windows::Forms::RichTextBox^   schemeBox;
    private: System::Windows::Forms::TextBox^       sourcePathBox;
    private: System::Windows::Forms::Button^        sourceFileButton;
    private: System::Windows::Forms::Button^        transformButton;
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog2;

    private: System::Windows::Forms::Label^         label1;
    private: System::Windows::Forms::Button^        sourceFolderButton;
    private: System::Windows::Forms::FolderBrowserDialog^  folderBrowserDialog;
    private: System::Windows::Forms::Label^         label2;
    private: System::Windows::Forms::ListBox^       logsBox;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Button^  loadFromFileButton;
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog1;

			 System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{     
			this->schemeBox = (gcnew System::Windows::Forms::RichTextBox());
			this->sourcePathBox = (gcnew System::Windows::Forms::TextBox());
			this->sourceFileButton = (gcnew System::Windows::Forms::Button());
			this->transformButton = (gcnew System::Windows::Forms::Button());
			this->openFileDialog2 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->sourceFolderButton = (gcnew System::Windows::Forms::Button());
			this->folderBrowserDialog = (gcnew System::Windows::Forms::FolderBrowserDialog());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->logsBox = (gcnew System::Windows::Forms::ListBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->loadFromFileButton = (gcnew System::Windows::Forms::Button());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->SuspendLayout();
			// 
			// schemeBox
			// 
			this->schemeBox->Font = (gcnew System::Drawing::Font(L"Consolas", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(238)));
			this->schemeBox->Location = System::Drawing::Point(12, 28);
			this->schemeBox->Name = L"schemeBox";
			this->schemeBox->Size = System::Drawing::Size(449, 233);
			this->schemeBox->TabIndex = 0;
			this->schemeBox->Text = L"";
			// 
			// sourcePathBox
			// 
			this->sourcePathBox->Location = System::Drawing::Point(467, 28);
			this->sourcePathBox->Name = L"sourcePathBox";
			this->sourcePathBox->Size = System::Drawing::Size(296, 20);
			this->sourcePathBox->TabIndex = 1;
			// 
			// sourceFileButton
			// 
			this->sourceFileButton->Location = System::Drawing::Point(467, 54);
			this->sourceFileButton->Name = L"sourceFileButton";
			this->sourceFileButton->Size = System::Drawing::Size(140, 20);
			this->sourceFileButton->TabIndex = 3;
			this->sourceFileButton->Text = L"File";
			this->sourceFileButton->UseVisualStyleBackColor = true;
			this->sourceFileButton->Click += gcnew System::EventHandler(this, &Window::fileClick);
			// 
			// transformButton
			// 
			this->transformButton->Location = System::Drawing::Point(467, 80);
			this->transformButton->Name = L"transformButton";
			this->transformButton->Size = System::Drawing::Size(294, 24);
			this->transformButton->TabIndex = 4;
			this->transformButton->Text = L"Transform";
			this->transformButton->UseVisualStyleBackColor = true;
			this->transformButton->Click += gcnew System::EventHandler(this, &Window::transformClick);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(467, 12);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(110, 13);
			this->label1->TabIndex = 5;
			this->label1->Text = L"XML to transformation";
			// 
			// sourceFolderButton
			// 
			this->sourceFolderButton->Location = System::Drawing::Point(613, 54);
			this->sourceFolderButton->Name = L"sourceFolderButton";
			this->sourceFolderButton->Size = System::Drawing::Size(150, 20);
			this->sourceFolderButton->TabIndex = 6;
			this->sourceFolderButton->Text = L"Folder";
			this->sourceFolderButton->UseVisualStyleBackColor = true;
			this->sourceFolderButton->Click += gcnew System::EventHandler(this, &Window::folderClick);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(467, 111);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(30, 13);
			this->label2->TabIndex = 7;
			this->label2->Text = L"Logs";
			// 
			// logsBox
			// 
			this->logsBox->FormattingEnabled = true;
			this->logsBox->Location = System::Drawing::Point(467, 127);
			this->logsBox->Name = L"logsBox";
			this->logsBox->Size = System::Drawing::Size(287, 160);
			this->logsBox->TabIndex = 8;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(12, 12);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(61, 13);
			this->label3->TabIndex = 9;
			this->label3->Text = L"XSLT code";
			// 
			// loadFromFileButton
			// 
			this->loadFromFileButton->Location = System::Drawing::Point(15, 267);
			this->loadFromFileButton->Name = L"loadFromFileButton";
			this->loadFromFileButton->Size = System::Drawing::Size(446, 20);
			this->loadFromFileButton->TabIndex = 10;
			this->loadFromFileButton->Text = L"Load from file";
			this->loadFromFileButton->UseVisualStyleBackColor = true;
			this->loadFromFileButton->Click += gcnew System::EventHandler(this, &Window::loadFromFileClick);
			// 
			// Window
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(773, 298);
			this->Controls->Add(this->loadFromFileButton);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->logsBox);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->sourceFolderButton);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->transformButton);
			this->Controls->Add(this->sourceFileButton);
			this->Controls->Add(this->sourcePathBox);
			this->Controls->Add(this->schemeBox);
			this->Name = L"Window";
			this->Text = L"WinXSLT";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

        System::Void fileClick(System::Object^  sender, System::EventArgs^  e);
        System::Void folderClick(System::Object^  sender, System::EventArgs^  e);
        System::Void transformClick(System::Object^  sender, System::EventArgs^  e);
		System::Void loadFromFileClick(System::Object^  sender, System::EventArgs^  e);
};
}
