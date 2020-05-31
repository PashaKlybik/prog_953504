using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.IO;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using System.Diagnostics;
using System.Drawing.Text;
using System.Net.Mail;
using System.Net;
using System.Threading;

namespace sCommander
{
    public partial class Form1 : Form
    {
        private string filePath, filePath2;     
        protected bool isFile = false, isFilefotInsert = true;
        protected string currentlySelectedItemName = "";
        protected string currentRoot = "";
        string oldPath = "", oldPathForCopy = "";
     //   Class1 load = new Class1();
        public Form1()
        {
            InitializeComponent();
           

            listView1.SmallImageList = imageList1;
            listView2.SmallImageList = imageList1;
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            driversDefinitionlv();
            loadFilesAndDirectories(listView1, filePath);

            driversDefinitionRt();
            loadFilesAndDirectories(listView2, filePath2);
            //Програмно задаем цвет панели
            this.panel1.BackColor = this.panel2.BackColor = Color.CornflowerBlue;
            //Добавляем событие для клика по иконке
            notifyIcon1.Click += notifyIcon1_Click;
        }
        private void Form1_FormClosed(object sender, FormClosedEventArgs e)
        {
            System.Environment.Exit(1);
        }

        private void DriveButton_Click(object sender, EventArgs e)
        {
            throw new NotImplementedException();
        }

        public void loadFilesAndDirectories(ListView list, string path)
        {
            string tempFilePath = "";
            FileAttributes fileAttr;

            try
            {
                if (isFile)
                {
                    tempFilePath = path + "/" + currentlySelectedItemName;
                    FileInfo fileDetails = new FileInfo(tempFilePath);
                    fileAttr = File.GetAttributes(tempFilePath);
                    Process.Start(tempFilePath);                                //Open file
                }
                else
                {
                    fileAttr = File.GetAttributes(path);

                }
                if((fileAttr & FileAttributes.Directory) == FileAttributes.Directory)
                {
                    DirectoryInfo fileList = new DirectoryInfo(path);
                    FileInfo[] files = fileList.GetFiles(); //Get all the files
                    DirectoryInfo[] dirs = fileList.GetDirectories();//Get all the dirs

                    string fileExtension = "";
                    int index = 0;
                    list.Items.Clear();
                    if (path != fileList.Root.ToString())
                    {
                        list.Items.Add("", 9);
                        index++;
                        currentRoot = fileList.Root.ToString();
                    }
                    for (int i = 0; i < dirs.Length; i++)
                    {
                        if (!toolStripMenuItem2.Checked)
                        {
                            //Do not show hidden files
                            if ((dirs[i].Attributes & FileAttributes.Hidden) == FileAttributes.Hidden)
                            {
                                continue;
                            }
                            list.Items.Add(dirs[i].Name, 0);
                            list.Items[index].SubItems.Add("");
                            list.Items[index].SubItems.Add("");
                            list.Items[index].SubItems.Add("");
                            list.Items[index].SubItems[1].Text = "<folder>";
                            list.Items[index++].SubItems[3].Text = dirs[i].LastWriteTime.ToShortDateString() + " " + dirs[i].LastWriteTime.ToShortTimeString();
                        }
                        else
                        {
                            list.Items.Add(dirs[i].Name, 0);
                            list.Items[index].SubItems.Add("");
                            list.Items[index].SubItems.Add("");
                            list.Items[index].SubItems.Add("");
                            list.Items[index].SubItems[1].Text = "<folder>";
                            list.Items[index++].SubItems[3].Text = dirs[i].LastWriteTime.ToShortDateString() + " " + dirs[i].LastWriteTime.ToShortTimeString();
                        }
                    }
                    for (int i = 0; i < files.Length; i++)
                    {
                        if((files[i].Attributes & FileAttributes.Hidden) == FileAttributes.Hidden) //Do not show hidden files
                        {
                            continue;
                        } 
                        fileExtension = files[i].Extension.ToUpper();
                        //Добавление иконок
                        switch (fileExtension)
                        {
                            case ".MP3":
                            case ".MP2":
                                list.Items.Add(files[i].Name, 5);
                                break;
                            case ".EXE":
                            case ".COM":
                                list.Items.Add(files[i].Name, 3);
                                break;
                            case ".MP4":
                            case ".MKV":
                            case ".AVI":
                                list.Items.Add(files[i].Name, 7);
                                break;
                            case ".PDF":
                                list.Items.Add(files[i].Name, 6);
                                break;
                            case ".DOC":
                            case "DOCX":
                                list.Items.Add(files[i].Name, 2);
                                break;
                            case ".TXT":
                                list.Items.Add(files[i].Name, 8);
                                break;
                            case ".PNG":
                            case ".JPG":
                            case ".JPEG":
                                list.Items.Add(files[i].Name, 4);
                                break;
                            default:
                                list.Items.Add(files[i].Name, 1);
                                break;                       
                        }
                        list.Items[index].SubItems.Add("");
                        list.Items[index].SubItems.Add("");
                        list.Items[index].SubItems.Add("");
                        list.Items[index].SubItems[1].Text = files[i].Extension.Substring(1, files[i].Extension.Length - 1);
                        list.Items[index].SubItems[2].Text = (files[i].Length / 1024 + 1).ToString();
                        list.Items[index++].SubItems[3].Text = (files[i].LastWriteTime.ToShortDateString() + " " + files[i].LastWriteTime.ToShortTimeString());
                    }                     
                }
            }
            catch(Exception e)
            {
                MessageBox.Show(
                    e.Message,
                    "Сообщение",
                    MessageBoxButtons.OK,
                    MessageBoxIcon.Information,
                    MessageBoxDefaultButton.Button1,
                    MessageBoxOptions.DefaultDesktopOnly);
                this.TopMost = true;
            }
        }

        public void loadButtonAction()
        {
            removeBackSlash();
            if (listView1.ContainsFocus == true)
            {
                loadFilesAndDirectories(listView1, filePath);
            }
            else
            {
                loadFilesAndDirectories(listView2, filePath2);
            }
            isFile = false;
        }
        //Определяем, какие виртуальные диски присутствуют на компютере для (ListView1) 
        public void driversDefinitionlv()
        {
            int sPoint = 5;
            foreach (var drive in DriveInfo.GetDrives())
            {
                Button driveButton = new Button
                {
                    BackColor = Color.LightGray,
                    Location = new Point(sPoint, 1),
                    Size = new Size(30, 20),
                    ForeColor = Color.Black,
                    Font = new Font("Dutch801 Rm BT", 9, FontStyle.Bold)
                };
                sPoint += 37;
                driveButton.Text = drive.Name;
                panel3.Controls.Add(driveButton);
                driveButton.Click += new EventHandler(DriveChangelv);
            }
            DriveInfo[] firstDrive = DriveInfo.GetDrives();
            //Присваивем путям начальные значения дисков
            filePath = firstDrive[0].Name;
            filePath2 = firstDrive[0].Name;
        }
        //Определяем, какие виртуальные диски присутствуют на компютере для (ListView2) 
        public void driversDefinitionRt()  
        {
            int sPoint = 5;
            foreach (var drive in DriveInfo.GetDrives())
            {
                Button driveButton = new Button
                {
                    BackColor = Color.LightGray,
                    Location = new Point(sPoint, 1),
                    Size = new Size(30, 20),
                    ForeColor = Color.Black,
                    Font = new Font("Dutch801 Rm BT", 9, FontStyle.Bold)
                };
                sPoint += 37;
                driveButton.Text = drive.Name;
                panel4.Controls.Add(driveButton);
                driveButton.Click += new EventHandler(DriveChangeRt);
            }
            DriveInfo[] firstDrive = DriveInfo.GetDrives();
            filePath = firstDrive[0].Name;
            filePath2 = firstDrive[0].Name;
        }
        //Если мы меняем диск (ListView1)
        private void DriveChangelv(object sender, EventArgs e)
        {
            filePath = ((Button)sender).Text.ToString();
            loadFilesAndDirectories(listView1, filePath);
        }
        //Если мы меняем диск (ListView2)
        private void DriveChangeRt(object sender, EventArgs e)
        {
            filePath2 = ((Button)sender).Text.ToString();
            loadFilesAndDirectories(listView2, filePath2);
        }

        public void removeBackSlash()
        {
            if (listView1.ContainsFocus == true)
            {
                string path = filePath;
                if (path.LastIndexOf("/") == path.Length - 1)
                {
                    filePath = path.Substring(0, path.Length - 1);
                }
            }
            else
            {
                string path = filePath2;
                if (path.LastIndexOf("/") == path.Length - 1)
                {
                    filePath2 = path.Substring(0, path.Length - 1);
                }
            }
        }
        //Возврат назад
        public void goBack()
        {
            try
            {
                if (listView1.ContainsFocus == true)
                {
                    removeBackSlash();
                    string path = filePath;
                    path = path.Substring(0, path.LastIndexOf("/"));
                    this.isFile = false;
                    filePath = path;
                    removeBackSlash();
                }
                else
                {
                    removeBackSlash();
                    string path = filePath2;
                    path = path.Substring(0, path.LastIndexOf("/"));
                    this.isFile = false;
                    filePath2 = path;
                    removeBackSlash();
                }
            }
            catch(Exception)
            {
                MessageBox.Show(
                    "Не удалось вернуться назад",
                    "Сообщение",
                    MessageBoxButtons.OK,
                    MessageBoxIcon.Information,
                    MessageBoxDefaultButton.Button1,
                    MessageBoxOptions.DefaultDesktopOnly);
                this.TopMost = true;
            }
        }
     
        private void listView1_DoubleClick(object sender, EventArgs e)
        {
            //   Получаем имя файла, по котором doubleClick 
            currentlySelectedItemName = listView1.Items[listView1.SelectedIndices[0]].Text;          

            FileAttributes fileAttr = File.GetAttributes(filePath + "/" + currentlySelectedItemName);
            if ((fileAttr & FileAttributes.Directory) == FileAttributes.Directory)                  // Проверяем, папка ли это
            {                                                                                       //    если да, то указываем новый путь
                isFile = false;                                                                     //   если нет, то открываем файл
                filePath = filePath + "/" + currentlySelectedItemName;
            }
            else
            {
                isFile = true;
            }
            //Откат назад 
            if (filePath != currentRoot && listView1.Items[listView1.SelectedIndices[0]].Text == "")
            {
                goBack();
                //Передаем на открытие
                loadButtonAction();                                                             
                return;
            }
            loadButtonAction();
        }
        private void listView2_DoubleClick(object sender, EventArgs e)
        {
            //   Получаем имя файла, по котором doubleClick 
            currentlySelectedItemName = listView2.Items[listView2.SelectedIndices[0]].Text;           

            FileAttributes fileAttr = File.GetAttributes(filePath2 + "/" + currentlySelectedItemName);
            if ((fileAttr & FileAttributes.Directory) == FileAttributes.Directory)              // Проверяем, папка ли это
            {                                                                                   //    если да, то указываем новый путь
                isFile = false;                                                                 //   если нет, то открываем файл
                filePath2 = filePath2 + "/" + currentlySelectedItemName;
            }
            else
            {
                isFile = true;
            }
            if (filePath2 != currentRoot && listView2.Items[listView2.SelectedIndices[0]].Text == "")
            {
                goBack();
                loadButtonAction();                                                             //Передаем на открытие
                return;
            }
            loadButtonAction();
        }
//-----------------------------------------------------------------------------------------------
//                                      Создание папки
        private void listView1_MouseUp(object sender, MouseEventArgs e)
        {
         
            //Если не выделен элемент, то контекстное меню формируется иначе
            if (e.Button == MouseButtons.Right && listView1.SelectedItems.Count == 0)
            {
                //Добавляем кнопку "Создать папку"
                ToolStripMenuItem createDirItem = new ToolStripMenuItem("Создать папку");
                ToolStripMenuItem insertMenuItem = new ToolStripMenuItem("Вставить");
                ToolStripMenuItem createFileItem = new ToolStripMenuItem("Создать файл");
                //Определяем набор ToolStripMenu, если вставлять после копирования
                if (oldPathForCopy != "")
                {
                    ToolStripMenuItem insert2MenuItem = new ToolStripMenuItem("Вставить");
                    // добавляем элементы в меню
                    contextMenuStrip1.Items.AddRange(new[] { createDirItem, insert2MenuItem, createFileItem });
                    insert2MenuItem.Click += insert2MenuItem_Click;
                }
                //Иначе определяем набор ToolStripMenu, если вставлять после вырезки
                else
                {
                    contextMenuStrip1.Items.AddRange(new[] { createDirItem, insertMenuItem, createFileItem });
                }
                //Добавляем событие создания папки
                createDirItem.Click += createDirItem_Click;
                insertMenuItem.Click += insertMenuItem_Click;
                createFileItem.Click += createFileItem_Click;
                //Задаем местоположение размещения контекстного меню
                contextMenuStrip1.Show(MousePosition, ToolStripDropDownDirection.Right);
            }
        }
       
        private void listView2_MouseUp(object sender, MouseEventArgs e)
        {
            //Если не выделен элемент, то контекстное меню формируется иначе
            if (e.Button == MouseButtons.Right && listView2.SelectedItems.Count == 0)
            {
                //Добавляем кнопку "Создать папку"
                ToolStripMenuItem createDirItem = new ToolStripMenuItem("Создать папку");
                ToolStripMenuItem insertMenuItem = new ToolStripMenuItem("Вставить");
                ToolStripMenuItem createFileItem = new ToolStripMenuItem("Создать файл");
                //Определяем набор ToolStripMenu, если вставлять после копирования
                if (oldPathForCopy != "")
                {
                    ToolStripMenuItem insert2MenuItem = new ToolStripMenuItem("Вставить");
                    // добавляем элементы в меню
                    contextMenuStrip1.Items.AddRange(new[] { createDirItem, insert2MenuItem, createFileItem });
                    insert2MenuItem.Click += insert2MenuItem_Click;
                }
                //Иначе определяем набор ToolStripMenu, если вставлять после вырезки
                else
                {
                    contextMenuStrip1.Items.AddRange(new[] { createDirItem, insertMenuItem, createFileItem });
                }
                //Добавляем событие создания папки
                createDirItem.Click += createDirItem_Click;
                insertMenuItem.Click += insertMenuItem_Click;
                createFileItem.Click += createFileItem_Click;
                //Задаем местоположение размещения контекстного меню
                contextMenuStrip1.Show(MousePosition, ToolStripDropDownDirection.Right);
            }
        }
 //----------------------------------------------------------------------------------------------------------------------------
        //Создаем панель
        Panel askWindow;
        bool onceChecked = false;
        void createFileItem_Click(object sender, EventArgs e)
        {
            onceChecked = false;
            Panel fileNamePanel = new Panel();
            fileNamePanel.Size = new Size(300, 130);
            fileNamePanel.Location = new Point(350, 150);
            fileNamePanel.BackgroundImage = new Bitmap(@"D:\\123.png");
            fileNamePanel.BackgroundImageLayout = ImageLayout.Stretch;
            askWindow = fileNamePanel;
            this.Controls.Add(fileNamePanel);
            fileNamePanel.BringToFront();
            TextBox fileName = new TextBox();
            fileName.BackColor = Color.WhiteSmoke;
            fileName.Size = new Size(190, 25);
            fileName.Location = new Point(50, 50);
            fileNamePanel.Controls.Add(fileName);

            fileName.Leave += DisposeTextBox1;
            fileName.Focus();

            Button okButton = new Button();
            okButton.Text = "Создать";
            okButton.Size = new Size(70, 25);
            okButton.Location = new Point(130, 95);
            okButton.ForeColor = Color.Black;
            okButton.Click += okButton_Click;
            fileNamePanel.Controls.Add(okButton);
            Button cancelButton = new Button();
            cancelButton.Text = "Отмена";
            cancelButton.Size = new Size(70, 25);
            cancelButton.Location = new Point(205, 95);
            cancelButton.ForeColor = Color.Black;
            cancelButton.Click += cancelButton_Click;
            fileNamePanel.Controls.Add(cancelButton);
            Label message = new Label();
            message.Text = "Введите имя файла с расширением";
            message.Size = new Size(230, 25);
            message.Location = new Point(50, 25);
            message.ForeColor = Color.Black;
            fileNamePanel.Controls.Add(message);
        }
    
        void DisposeTextBox1(object sender, EventArgs e)
        {
            var tb = (sender as TextBox);
           
            int countItems = listView1.Items.Count;
            FileInfo file = new FileInfo(filePath + "/" + tb.Text);
            if (!file.Exists)
            {
                File.Create(filePath + "/" + tb.Text).Close();

                loadFilesAndDirectories(listView1, filePath);
                loadFilesAndDirectories(listView2, filePath2);
            }
            if (countItems == listView1.Items.Count && onceChecked == false)
            {
                MessageBox.Show(
                "Такое уже было...",
                "Сообщение",
                MessageBoxButtons.OK,
                MessageBoxIcon.Information,
                MessageBoxDefaultButton.Button1,
                MessageBoxOptions.DefaultDesktopOnly);
                //Отображаем форму на переднем плане
                this.TopMost = true;
            }           
            onceChecked = true;
            cancelButton_Click((sender as TextBox), null);
            tb.Dispose();
        }
        void cancelButton_Click(object sender, EventArgs e)
        {
            this.Controls.Remove(askWindow);
        }
        //Снимаем фокус с TB
        void okButton_Click(object sender, EventArgs e)
        {

        }
//---------------------------------------------------------------------------------------------------------------------
        //Событие создания папки
        void createDirItem_Click(object sender, EventArgs e)
        {
            //Если работаем с ListView1
            if (listView1.ContainsFocus == true)
            {
                //Создаем textBoх, настраиваем его параметры и вставляем в место будующей папки
                TextBox tbox = new TextBox();
                this.Controls.Add(tbox);
                tbox.Width = 258;
                ListViewItem item = listView1.Items[listView1.Items.Count - 1];
                if (item != null)
                {
                    tbox.Left = 20;
                    tbox.Top = item.Position.Y + 17;
                    tbox.Text = "Новая папка"; 
                    tbox.Leave += DisposeTextBox;
                    tbox.KeyPress += TextBoxKeyPress;
                    listView1.Controls.Add(tbox);
                    tbox.Focus();
                    tbox.Select(tbox.Text.Length, 1);
                }
            }
            //Если работаем с ListView2
            else
            {
                //Создаем textBoх, настраиваем его параметры и вставляем в место будующей папки
                TextBox tbox = new TextBox();
                this.Controls.Add(tbox);
                tbox.Width = 258;
                ListViewItem item = listView2.Items[listView2.Items.Count - 1];
                if (item != null)
                {
                    tbox.Left = 20;
                    tbox.Top = item.Position.Y + 17;
                    tbox.Text = "Новая папка";
                    tbox.Leave += DisposeTextBox;
                    tbox.KeyPress += TextBoxKeyPress;
                    listView2.Controls.Add(tbox);
                    tbox.Focus();
                    tbox.Select(tbox.Text.Length, 1);
                }
            }
            contextMenuStrip1.Items.Clear();            //Очищаем элементы контекстного меню
        }
        //Проверка, разрушен ли TB, если да, то больше не проверяем на равенство кол-во файлов
        bool disposeTextBox = false;
        //Разрушаем TB
        void DisposeTextBox(object sender, EventArgs e)
        {
            var tb = (sender as TextBox);
            int countItems = listView1.Items.Count;
            //Выедяем элементы, 
            //  var item = listView1.GetItemAt(0, tb.Top - 15);
            if (listView1.ContainsFocus == true)
            {
                countItems = listView1.Items.Count;
                string tempFilePath = filePath;
                DirectoryInfo dirInfo = new DirectoryInfo(tempFilePath);
                //Создаем папку с указанным текстом из TB
                dirInfo.CreateSubdirectory(tb.Text);
                loadFilesAndDirectories(listView1, filePath);
                if (countItems == listView1.Items.Count && disposeTextBox == false)
                {
                    disposeTextBox = true;
                    panel5.BackColor = panel1.BackColor = panel2.BackColor = Color.LightPink;
                    DialogResult result = MessageBox.Show(
                    "А ты оригинальный! Может придумаешь что-нибудь поинтереснее?",
                    "Сообщение",
                    MessageBoxButtons.OK,
                    MessageBoxIcon.Information,
                    MessageBoxDefaultButton.Button1,
                    MessageBoxOptions.DefaultDesktopOnly);
                    //Отображаем форму на переднем плане
                    this.TopMost = true;
                }
                loadFilesAndDirectories(listView1, filePath);
            }
            else
            {
                countItems = listView2.Items.Count;
                string tempFilePath = filePath2;
                DirectoryInfo dirInfo = new DirectoryInfo(tempFilePath);
                //Создаем папку с указанным текстом из TB
                dirInfo.CreateSubdirectory(tb.Text);
                loadFilesAndDirectories(listView2, filePath2);
                if (countItems == listView2.Items.Count && disposeTextBox == false)
                {
                    disposeTextBox = true;
                    panel5.BackColor = panel1.BackColor = panel2.BackColor = Color.LightPink;
                   // this.Refresh();
                    MessageBox.Show(
                    "А ты оригинальный! Может придумаешь что-нибудь поинтереснее?",
                    "Сообщение",
                    MessageBoxButtons.OK,
                    MessageBoxIcon.Information,
                    MessageBoxDefaultButton.Button1,
                    MessageBoxOptions.DefaultDesktopOnly);
                    //Отображаем форму на переднем плане
                    this.TopMost = true;
                }
                loadFilesAndDirectories(listView2, filePath2);
            }
            disposeTextBox = true;
            tb.Dispose();
            disposeTextBox = true;
        }
        //Определяем событие для нажатия клавиш при вводе названия папки
        //Если Enter - завершаем
        //Если Esc - отмена
        void TextBoxKeyPress(object sender, KeyPressEventArgs e)
        {
            if (e.KeyChar == 13)
            {
                DisposeTextBox((sender as TextBox), null);
            }
            if (e.KeyChar == 27)
                (sender as TextBox).Dispose();
        }
      
//---------------------------------------------------------------------------------------------------
//                                              УДАЛЕНИЕ, КОПИРОВАНИЕ, ОТПРАВКА
        private void listView1_MouseClick(object sender, MouseEventArgs e)
        {
            listView1.BackColor = Color.Azure;
            listView2.BackColor = Color.White;
            if (e.Button == MouseButtons.Right && listView1.SelectedItems.Count != 0)
            {
                currentlySelectedItemName = listView1.Items[listView1.SelectedIndices[0]].Text;
                FileAttributes fileAttr = File.GetAttributes(filePath + "/" + currentlySelectedItemName);
                if (!((fileAttr & FileAttributes.Directory) == FileAttributes.Directory))
                {
                    ToolStripMenuItem replaceMenuItem = new ToolStripMenuItem("Копировать");
                    contextMenuStrip1.Items.Add(replaceMenuItem );
                    replaceMenuItem.Click += copy2MenuItem_Click;
                    //Отправка письма
                    ToolStripMenuItem sendMessage = new ToolStripMenuItem("Отправить");
                    contextMenuStrip1.Items.Add(sendMessage);
                    sendMessage.Click += sendMessage_Click;
                }
                ToolStripMenuItem copyMenuItem = new ToolStripMenuItem("Вырезать");
                ToolStripMenuItem deleteMenuItem = new ToolStripMenuItem("Удалить");
                //Проверяем, есть ли на данный момент файл в буфере
                if (oldPath != "")
                {
                    ToolStripMenuItem insertMenuItem = new ToolStripMenuItem("Вставить");
                    // добавляем элементы в меню
                    contextMenuStrip1.Items.AddRange(new[] { copyMenuItem, deleteMenuItem, insertMenuItem });
                    insertMenuItem.Click += insertMenuItem_Click;
                }
                else
                {
                    // добавляем элементы в меню
                    contextMenuStrip1.Items.AddRange(new[] { copyMenuItem, deleteMenuItem});
                }
                // устанавливаем обработчики событий для меню
                copyMenuItem.Click += copyMenuItem_Click;
                deleteMenuItem.Click += deleteMenuItem_Click;  
                //Задаем местоположение размещения контекстного меню
                contextMenuStrip1.Show(MousePosition, ToolStripDropDownDirection.Right);
            }
        }
        private void listView2_MouseClick(object sender, MouseEventArgs e)
        {
            listView2.BackColor = Color.Azure;
            listView1.BackColor = Color.White;
            //Создаем контекстное меню(если вызов относится к выбранному элементу)
            if (e.Button == MouseButtons.Right && listView2.SelectedItems.Count != 0)
            {
                currentlySelectedItemName = listView2.Items[listView2.SelectedIndices[0]].Text;
                FileAttributes fileAttr = File.GetAttributes(filePath2 + "/" + currentlySelectedItemName);
                if (!((fileAttr & FileAttributes.Directory) == FileAttributes.Directory))
                {
                    ToolStripMenuItem replaceMenuItem = new ToolStripMenuItem("Копировать");
                    contextMenuStrip1.Items.Add(replaceMenuItem);
                    replaceMenuItem.Click += copy2MenuItem_Click;
                    //Отправка письма
                    ToolStripMenuItem sendMessage = new ToolStripMenuItem("Отправить");
                    contextMenuStrip1.Items.Add(sendMessage);
                    sendMessage.Click += sendMessage_Click;
                }
                ToolStripMenuItem copyMenuItem = new ToolStripMenuItem("Вырезать");
                ToolStripMenuItem deleteMenuItem = new ToolStripMenuItem("Удалить");
                //Проверяем, есть ли на данный момент файл в буфере
                if (oldPath != "")
                {
                    ToolStripMenuItem insertMenuItem = new ToolStripMenuItem("Вставить");
                    // добавляем элементы в меню
                    contextMenuStrip1.Items.AddRange(new[] { copyMenuItem, deleteMenuItem, insertMenuItem });
                    insertMenuItem.Click += insertMenuItem_Click;
                }
                else
                {
                    // добавляем элементы в меню
                    contextMenuStrip1.Items.AddRange(new[] { copyMenuItem, deleteMenuItem });
                }
                copyMenuItem.Click += copyMenuItem_Click;
                deleteMenuItem.Click += deleteMenuItem_Click;
                //Задаем местоположение размещения контекстного меню
                contextMenuStrip1.Show(MousePosition, ToolStripDropDownDirection.Right);
            }
        }

        // Удалить файл или директорию
        void deleteMenuItem_Click(object sender, EventArgs e)
        {               
            if (listView1.ContainsFocus == true)
            {
                FileAttributes fileAttr = File.GetAttributes(filePath + "/" + listView1.Items[listView1.SelectedIndices[0]].Text);
                if ((fileAttr & FileAttributes.Directory) == FileAttributes.Directory)                  // Проверяем, папка ли это
                {                                                                                       //    если да, то указываем новый путь
                    string dirName = filePath + "/" + listView1.Items[listView1.SelectedIndices[0]].Text;
                    Directory.Delete(dirName, true);
                }
                else             //Если это файл, то указываем его путь и удаляем
                {
                    string tempFilePath = filePath + "/" + listView1.Items[listView1.SelectedIndices[0]].Text;
                    FileInfo fileInf = new FileInfo(tempFilePath);
                    if (fileInf.Exists)
                    {
                        fileInf.Delete();
                    }
                }
                loadFilesAndDirectories(listView1, filePath);   //Обновляем данные
            }
            else
            {
                FileAttributes fileAttr = File.GetAttributes(filePath2 + "/" + listView2.Items[listView2.SelectedIndices[0]].Text);
                if ((fileAttr & FileAttributes.Directory) == FileAttributes.Directory)                  // Проверяем, папка ли это
                {                                                                                       //    если да, то указываем новый путь
                    string dirName = filePath2 + "/" + listView2.Items[listView2.SelectedIndices[0]].Text;
                    Directory.Delete(dirName, true);
                }
                else           //Если это файл, то указываем его путь и удаляем
                {
                    string tempFilePath = filePath2 + "/" + listView2.Items[listView2.SelectedIndices[0]].Text;
                    FileInfo fileInf = new FileInfo(tempFilePath);
                    if (fileInf.Exists)
                    {
                        fileInf.Delete();
                    }
                }
                loadFilesAndDirectories(listView2, filePath2);   //Обновляем данные
            }
           
            contextMenuStrip1.Items.Clear();            //Очищаем элементы контекстного меню
        }
        // КОПИРОВАНИЕ ДИРЕКТОРИЙ И ПАПОК
        void copyMenuItem_Click(object sender, EventArgs e)
        {
            //Если фокус на 1 ЛВ, то запоимнаем путь, из которого копируем 
            if (listView1.ContainsFocus == true)
            {
                FileAttributes fileAttr = File.GetAttributes(filePath + "/" + listView1.Items[listView1.SelectedIndices[0]].Text);
                if ((fileAttr & FileAttributes.Directory) == FileAttributes.Directory)
                {
                    oldPath = filePath + "/" + listView1.Items[listView1.SelectedIndices[0]].Text;
                    isFilefotInsert = false;
                }
                //Если файл !!!!!!!!!!!!
                else
                {
                    isFilefotInsert = true;
                    oldPath = filePath + "/" + listView1.Items[listView1.SelectedIndices[0]].Text;
                }
            }
            //Если фокус на 2 ЛВ, то запоимнаем путь, из которого копируем 
            else
            {
                FileAttributes fileAttr = File.GetAttributes(filePath2 + "/" + listView2.Items[listView2.SelectedIndices[0]].Text);
                if ((fileAttr & FileAttributes.Directory) == FileAttributes.Directory)
                {
                    oldPath = filePath2 + "/" + listView2.Items[listView2.SelectedIndices[0]].Text;
                    isFilefotInsert = false;
                }
                else
                {
                    isFilefotInsert = true;
                    oldPath = filePath2 + "/" + listView2.Items[listView2.SelectedIndices[0]].Text;
                }
            }
        }
        //Вставка из буфера(OldPath)
        void insertMenuItem_Click(object sender, EventArgs e)
        {
            //Если вставляем директорию
            if (!isFilefotInsert)
            {
                DirectoryInfo dirInfo = new DirectoryInfo(oldPath);
                string newPath;
                try
                {
                    //Если фокус на 1 ЛВ
                    if (listView1.ContainsFocus == true)
                    {
                        //Определяем путь, куда вставляем
                        newPath = filePath + "/" + listView2.Items[listView2.SelectedIndices[0]].Text;
                        dirInfo.MoveTo(newPath);
                        oldPath = "";
                    }
                    //Если фокус на 2 ЛВ
                    else
                    {
                        //Определяем путь, куда втсавляем
                        newPath = filePath2 + "/" + listView1.Items[listView1.SelectedIndices[0]].Text;
                        dirInfo.MoveTo(newPath);
                        oldPath = "";
                    }
                }
                catch(Exception ex)
                {
                    panel5.BackColor = panel1.BackColor = panel2.BackColor = Color.LightPink;
                    this.Refresh();
                    MessageBox.Show(
                    ex.Message,
                    "Сообщение",
                    MessageBoxButtons.OK,
                    MessageBoxIcon.Information,
                    MessageBoxDefaultButton.Button1,
                    MessageBoxOptions.DefaultDesktopOnly);
                    //Отображаем форму на переднем плане
                    this.TopMost = true;
                }
            }
            //Если вставляем файл
            else
            {
                try
                {
                    FileInfo fileInf = new FileInfo(oldPath);
                    string newPath;
                    //Если фокус на 1 ЛВ
                    if (listView1.ContainsFocus == true)
                    {
                        //Определяем путь, куда вставляем
                        newPath = filePath + "/" + listView2.Items[listView2.SelectedIndices[0]].Text;
                        fileInf.MoveTo(newPath);
                        oldPath = "";
                    }
                    //Если фокус на 2 ЛВ
                    else
                    {
                        newPath = filePath2 + "/" + listView1.Items[listView1.SelectedIndices[0]].Text;
                        fileInf.MoveTo(newPath);
                        oldPath = "";
                    }
                }
                catch(UnauthorizedAccessException)
                {
                    panel5.BackColor = panel1.BackColor = panel2.BackColor = Color.LightPink;
                    this.Refresh();
                    MessageBox.Show(
                    "Путь недоступен для перемещения",
                    "Ошибка",
                    MessageBoxButtons.OK,
                    MessageBoxIcon.Information,
                    MessageBoxDefaultButton.Button1,
                    MessageBoxOptions.DefaultDesktopOnly);
                    //Отображаем форму на переднем плане
                    this.TopMost = true;
                }
                catch(Exception ex)
                {
                    panel5.BackColor = panel1.BackColor = panel2.BackColor = Color.LightPink;
                    this.Refresh();
                    MessageBox.Show(
                    ex.Message,
                    "Ошибка",
                    MessageBoxButtons.OK,
                    MessageBoxIcon.Information,
                    MessageBoxDefaultButton.Button1,
                    MessageBoxOptions.DefaultDesktopOnly);
                    //Отображаем форму на переднем плане
                    this.TopMost = true;
                }
            }
            //Обновляем внешний вид
            loadFilesAndDirectories(listView1, filePath);
            loadFilesAndDirectories(listView2, filePath2);
        }
        void copy2MenuItem_Click(object sender, EventArgs e)
        {
            //Если фокус на 1 ЛВ, то запоимнаем путь, из которого копируем 
            if (listView1.ContainsFocus == true)
            {
                isFilefotInsert = true;
                oldPathForCopy = filePath + "/" + listView1.Items[listView1.SelectedIndices[0]].Text;             
            }
            //Если фокус на 2 ЛВ, то запоимнаем путь, из которого копируем 
            else
            {
                isFilefotInsert = true;
                oldPathForCopy = filePath2 + "/" + listView2.Items[listView2.SelectedIndices[0]].Text;
            }
        }
        void insert2MenuItem_Click(object sender, EventArgs e)
        {
            try
            {
                FileInfo fileInf = new FileInfo(oldPathForCopy);
                string newPath;
                //Если фокус на 1 ЛВ
                if (listView1.ContainsFocus == true)
                {
                    //Определяем путь, куда вставляем
                    newPath = filePath + "/" + listView2.Items[listView2.SelectedIndices[0]].Text;
                    fileInf.CopyTo(newPath);
                    oldPathForCopy = "";
                }
                //Если фокус на 2 ЛВ
                else
                {
                    newPath = filePath2 + "/" + listView1.Items[listView1.SelectedIndices[0]].Text;
                    fileInf.CopyTo(newPath);
                    oldPathForCopy = "";
                }
            }
            catch (UnauthorizedAccessException)
            {
                panel5.BackColor = panel1.BackColor = panel2.BackColor = Color.LightPink;
                this.Refresh();
                MessageBox.Show(
                "Путь недоступен для перемещения",
                "Ошибка",
                MessageBoxButtons.OK,
                MessageBoxIcon.Information,
                MessageBoxDefaultButton.Button1,
                MessageBoxOptions.DefaultDesktopOnly);
                //Отображаем форму на переднем плане
                this.TopMost = true;
            }
            catch (Exception ex)
            {
                panel5.BackColor = panel1.BackColor = panel2.BackColor = Color.LightPink;
                this.Refresh();
                MessageBox.Show(
                ex.Message,
                "Ошибка",
                MessageBoxButtons.OK,
                MessageBoxIcon.Information,
                MessageBoxDefaultButton.Button1,
                MessageBoxOptions.DefaultDesktopOnly);
                //Отображаем форму на переднем плане
                this.TopMost = true;
            }

            //Обновляем внешний вид
            loadFilesAndDirectories(listView1, filePath);
            loadFilesAndDirectories(listView2, filePath2);
        }
        void sendMessage_Click(object sender, EventArgs e)
        {

            DialogResult result =  MessageBox.Show(
            "Отправить письмо по адресу: " + toolStripTextBox1.Text + " ?",
            "Сообщение",
            MessageBoxButtons.YesNo,
            MessageBoxIcon.Question,
            MessageBoxDefaultButton.Button1,
            MessageBoxOptions.DefaultDesktopOnly);
            //Отображаем форму на переднем плане
            this.TopMost = true;
            if (result == DialogResult.Yes)
            {
                // отправитель - устанавливаем адрес и отображаемое в письме имя
                MailAddress from = new MailAddress(toolStripTextBox2.Text, "sCommander");
                // кому отправляем
                MailAddress to = new MailAddress(toolStripTextBox1.Text);
                // создаем объект сообщения
                MailMessage m = new MailMessage(from, to);
                m.Attachments.Add(new Attachment(filePath + "/" + listView1.Items[listView1.SelectedIndices[0]].Text));
                // тема письма
                m.Subject = "Тест";
                // текст письма
                m.Body = "Привет, это тебе:\n";
                // письмо представляет код html
                m.IsBodyHtml = true;
                // адрес smtp-сервера и порт, с которого будем отправлять письмо
                SmtpClient smtp = new SmtpClient(toolStripTextBox4.Text, Convert.ToInt32(toolStripTextBox5.Text));
                // логин и пароль
                smtp.Credentials = new NetworkCredential(toolStripTextBox2.Text, toolStripTextBox3.Text);
                smtp.EnableSsl = true;
                smtp.Send(m);
            }
        }
//----------------------------------------------------------------------------------------------------------
        private void listView2_MouseDown(object sender, MouseEventArgs e)
        {
            //Очищаем список contextMenuStrip, чтобы оно не вызывалось без выбранного элмента
            contextMenuStrip1.Items.Clear();
            //Смена цвета панелей после ошибки
            panel1.BackColor = panel2.BackColor = Color.CornflowerBlue;
            panel5.BackColor = Color.LightSteelBlue;
        }

        private void listView1_MouseDown(object sender, MouseEventArgs e)
        {
            //Очищаем список contextMenuStrip, чтобы оно не вызывалось без выбранного элмента
            contextMenuStrip1.Items.Clear();
            //Смена цвета панелей после ошибки
            panel1.BackColor = panel2.BackColor = Color.CornflowerBlue;
            panel5.BackColor = Color.LightSteelBlue;
        }
//---------------------------------------------------------------------------------------------------------------------------
//                                                      ВИД ТАБЛИЦЫ ЭЛЕМЕНТОВ
        private void titlToolStripMenuItem_Click(object sender, EventArgs e)
        {
            changeToolStripMenuItem();
            titlToolStripMenuItem.Checked = true;
            listView1.View = View.Tile;
            listView2.View = View.Tile;
        }

        private void listToolStripMenuItem_Click(object sender, EventArgs e)
        {
            changeToolStripMenuItem();
            listToolStripMenuItem.Checked = true;
            listView1.View = View.List;
            listView2.View = View.List;
        }

        private void smallIconToolStripMenuItem_Click(object sender, EventArgs e)
        {
            changeToolStripMenuItem();
            smallIconToolStripMenuItem.Checked = true;
            listView1.View = View.SmallIcon;
            listView2.View = View.SmallIcon;
        }

        private void largeIconToolStripMenuItem_Click(object sender, EventArgs e)
        {
            changeToolStripMenuItem();
            largeIconToolStripMenuItem.Checked = true;
            listView1.View = View.LargeIcon;
            listView2.View = View.LargeIcon;
        }

        private void detailsToolStripMenuItem_Click(object sender, EventArgs e)
        {
            changeToolStripMenuItem();
            detailsToolStripMenuItem.Checked = true;
            listView1.View = View.Details;
            listView2.View = View.Details;
        }
        //Отменить checked на всех элементах
        private void changeToolStripMenuItem()
        {
            titlToolStripMenuItem.Checked = false;
            smallIconToolStripMenuItem.Checked = false;
            largeIconToolStripMenuItem.Checked = false;
            detailsToolStripMenuItem.Checked = false;
            listToolStripMenuItem.Checked = false;
        }
        //--------------------------------------------------------------------------------------------------------------------------
        //Смена цвета панелей после ошибки
        private void Form1_MouseClick(object sender, MouseEventArgs e)
        {
            panel1.BackColor = panel2.BackColor = Color.CornflowerBlue;
            panel5.BackColor = Color.LightSteelBlue;
        }
        //Отображение окна формы(по умолчанию)
        void notifyIcon1_Click(object sender, EventArgs e)
        {
            this.WindowState = FormWindowState.Normal;
        }
        //Перегрузить внешний вид
        private void button1_Click(object sender, EventArgs e)
        {
            loadFilesAndDirectories(listView1, filePath);
            loadFilesAndDirectories(listView2, filePath2);
        }
    }
}
