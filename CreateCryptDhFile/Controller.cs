using System;
using System.IO;
using System.Text;
using System.Windows.Forms;
using CreateCryptDhFile.Interface;

namespace CreateCryptDhFile
{
    class Controller
    {
        public void BrowseButtonClick(object sender, EventArgs e)
        {
            var dialog = new FolderBrowserDialog();
            dialog.ShowDialog();
            _fileDirectory = dialog.SelectedPath;
            _view.SetFileDirTextBox(_fileDirectory);
        }

        public void CreateButtonClick(object sender, EventArgs e)
        {
            FileCreateInDirectory(_fileDirectory);
        }

        private void FileCreateInDirectory(String directiory)
        {
            if (directiory != "")
            {
                try
                {
                    directiory = directiory + @"\gkeydh.bin";
                    if (File.Exists(directiory))
                    {
                         //Здесь может быть реализована удалить старый файл или нет
                        File.Delete(directiory);
                    }

                    using (var fs = File.Create(directiory))
                    {
                        var bytes = new UTF8Encoding(true).GetBytes("File is create");
                        fs.Write(bytes, 0, bytes.Length);
                        _view.InformationMessageShow("Файл успешно сгенерирован");
                        _view.SetImage(true);
                    }
                }
                catch (Exception)
                {
                    _view.InformationMessageShow("Не удалось создать файл по указанному пути");
                }
            }
            else
            {
                _view.InformationMessageShow("Указан не правильный путь");
            }
        }

        #region Constructor
        public Controller(IView view)
        {
            _view = view;
            _fileDirectory = "";
            _view.BrowseButton += BrowseButtonClick;
            _view.CreateButton += CreateButtonClick;

        }
        #endregion

        #region Filed
        private String _fileDirectory;
        private IView _view;

        #endregion
    }
}
