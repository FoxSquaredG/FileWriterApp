
// FileWriterAppDlg.cpp: файл реализации
//

#include "pch.h"
#include "framework.h"
#include "FileWriterApp.h"
#include "FileWriterAppDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Диалоговое окно CAboutDlg используется для описания сведений о приложении

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

// Реализация
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Диалоговое окно CFileWriterAppDlg



CFileWriterAppDlg::CFileWriterAppDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FILEWRITERAPP_DIALOG, pParent)
	, m_filePath(_T(""))
	, m_textToWrite(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFileWriterAppDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_FILEPATH, m_filePath);
	DDX_Text(pDX, IDC_EDIT_TEXT, m_textToWrite);
}

BEGIN_MESSAGE_MAP(CFileWriterAppDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_WRITE, &CFileWriterAppDlg::OnBnClickedButtonWrite)
	ON_BN_CLICKED(IDC_BUTTON_BROWSE, &CFileWriterAppDlg::OnBnClickedButtonBrowse)
END_MESSAGE_MAP()


// Обработчики сообщений CFileWriterAppDlg

BOOL CFileWriterAppDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Добавление пункта "О программе..." в системное меню.

	// IDM_ABOUTBOX должен быть в пределах системной команды.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	// TODO: добавьте дополнительную инициализацию

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

void CFileWriterAppDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CFileWriterAppDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CFileWriterAppDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CFileWriterAppDlg::OnBnClickedButtonWrite()
{
	// 1. Получаем данные из полей ввода в наши переменные m_filePath и m_textToWrite
	UpdateData(TRUE);

	// 2. Проверяем, что поля не пустые
	if (m_filePath.IsEmpty())
	{
		AfxMessageBox(_T("Пожалуйста, укажите путь к файлу."));
		return; // Выходим из функции, если путь не указан
	}

	if (m_textToWrite.IsEmpty())
	{
		AfxMessageBox(_T("Пожалуйста, введите текст для записи."));
		return; // Выходим из функции, если текст пуст
	}

	//// 3. Запись в файл
	//CStdioFile file; // Используем CStdioFile для удобной работы с текстом
	//// Открываем файл в режиме "дозаписи".
	//// CFile::modeCreate - создать файл, если он не существует.
	//// CFile::modeNoTruncate - не удалять содержимое, если файл существует.
	//// CFile::modeWrite - открыть для записи.
	//if (file.Open(m_filePath, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite))
	//{
	//	// Перемещаем указатель в конец файла для добавления новой строки
	//	file.SeekToEnd();

	//	//if (!bFirstLine) {
	//	//	file.WriteString(_T("======= new ===========================================\n"));
	//	//	bFirstLine = true;
	//	//}

	//	// Записываем текст и добавляем символ новой строки
	//	file.WriteString(m_textToWrite + _T("\n"));

	//	// Закрываем файл
	//	file.Close();

	//	// 4. Очищаем поле ввода текста
	//	m_textToWrite.Empty(); // Очищаем переменную

	//	// 5. Обновляем интерфейс, чтобы очищенное поле отобразилось на форме
	//	UpdateData(FALSE);

	//	// Опционально: сообщаем об успехе
	//	// AfxMessageBox(_T("Текст успешно добавлен в файл!"));
	//}
	//else
	//{
	//	// Если файл не удалось открыть (например, нет прав доступа или неверный путь)
	//	AfxMessageBox(_T("Ошибка! Не удалось открыть файл для записи."));
	//}

	// 3. Получаем текущее время и дату
	CTime currentTime = CTime::GetCurrentTime();

	// 4. Запись в файл
	CStdioFile file;
	if (file.Open(m_filePath, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite))
	{
		// Проверяем, является ли файл новым.
		//// Если его длина равна 0, значит, он только что был создан.
		//if (file.GetLength() == 0)
		//{
		if (!bFirstLine) {
			// Это новый файл, записываем заголовок с текущей датой
			CString dateString = currentTime.Format(_T("%d.%m.%Y")); // Формат ДД.ММ.ГГГГ
			CString header = _T("NewLine ") + dateString + _T("========================== \n");
			file.WriteString(header);
		}

		// Перемещаем указатель в конец файла для дозаписи
		file.SeekToEnd();

		// Формируем основную строку для записи
		CString timeString = currentTime.Format(_T("%H:%M:%S")); // Формат ЧЧ:ММ:СС
		CString className = _T("CFileWriterAppDlg"); // Имя класса-источника

		CString lineToWrite = timeString + _T(" ") + className + _T(" ") + m_textToWrite + _T("\n");

		// Записываем сформированную строку
		file.WriteString(lineToWrite);

		// Закрываем файл
		file.Close();

		// Очищаем поле ввода текста
		m_textToWrite.Empty();

		// Обновляем интерфейс
		UpdateData(FALSE);
	}
	else
	{
		AfxMessageBox(_T("Ошибка! Не удалось открыть файл для записи."));
	}
}

void CFileWriterAppDlg::OnBnClickedButtonBrowse()
{
	// Создаем диалог для выбора файла.
 // FALSE в первом параметре означает, что это диалог "Сохранить как" (Save As),
 // что позволяет пользователю вводить новое имя файла.
 // TRUE означало бы диалог "Открыть" (Open), где можно выбрать только существующий файл.
 //
 // Параметры конструктора CFileDialog:
 // 1. bOpenFileDialog: FALSE для "Сохранить как".
 // 2. lpszDefExt: Расширение по умолчанию (например, "txt").
 // 3. lpszFileName: Имя файла по умолчанию (можно оставить NULL).
 // 4. dwFlags: Флаги для настройки диалога.
 //    OFN_HIDEREADONLY - скрыть галочку "Только для чтения".
 //    OFN_OVERWRITEPROMPT - предупреждать, если файл уже существует.
 // 5. lpszFilter: Фильтр типов файлов.
 // 6. pParentWnd: Указатель на родительское окно.

	CString filter = _T("Текстовые файлы (*.txt)|*.txt|Все файлы (*.*)|*.*||");
	CFileDialog dlg(FALSE, _T("txt"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, filter, this);

	// Показываем диалоговое окно. Если пользователь нажал "Сохранить" (или "ОК"),
	// метод DoModal() вернет IDOK.
	if (dlg.DoModal() == IDOK)
	{
		// Получаем полный путь к выбранному файлу
		m_filePath = dlg.GetPathName();

		// Обновляем поле ввода на форме, чтобы показать выбранный путь
		UpdateData(FALSE);
	}
}
