using System;
using System.Windows;
using System.Windows.Media.Imaging;
using CreateCryptDhFile.Interface;

namespace CreateCryptDhFile
{
    /// <summary>
    /// Логика взаимодействия для MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window, IView
    {
        #region Constructor
        public MainWindow()
        {
            _controller = new Controller(this);
            InitializeComponent();
        }
        #endregion

        #region IView
        public event EventHandler BrowseButton;
        public event EventHandler CreateButton;
        #endregion

        #region Events
        private void browsDirButton_Click(object sender, EventArgs e)
        {
            if (BrowseButton != null)
            {
                BrowseButton(sender, e);
            }
        }

        private void createFileButton_Click(object sender, EventArgs e)
        {
            if (CreateButton != null)
            {
                CreateButton(sender, e);
            }
        }
        #endregion

        #region methods
        public void SetFileDirTextBox(String dir)
        {
            fileDirTestBox.Text = dir;
        }

        public void InformationMessageShow(String msg)
        {
            CreateFileLabel.Content = msg;
        }

        public void SetImage(bool flag)
        {
            if (flag)
            {
               var imgTrue = new BitmapImage();
               imgTrue.BeginInit();
               imgTrue.UriSource = new Uri(@"D:\Диплом\Рабочий репозиторий\tk_project_windows\CreateCryptDhFile\ImageRunOk.jpg", UriKind.Absolute);
               imgTrue.CacheOption = BitmapCacheOption.OnLoad;
               imgTrue.EndInit();
               Img.DataContext = imgTrue;
            }
            else
            {
                var imgFalse = new BitmapImage();
                imgFalse.BeginInit();
                imgFalse.UriSource = new Uri(@"D:\Диплом\Рабочий репозиторий\tk_project_windows\CreateCryptDhFile\ImageRunOk.jpg", UriKind.Absolute);
                imgFalse.EndInit();
                Img.DataContext = imgFalse;
            }
        }
        #endregion

        #region Filder
        private Controller _controller;
        #endregion
    }
}
