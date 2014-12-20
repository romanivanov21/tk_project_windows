using System;

namespace CreateCryptDhFile.Interface
{
    interface IView
    {
        event EventHandler BrowseButton;
        event EventHandler CreateButton;

        void SetFileDirTextBox(String firectory);
        void InformationMessageShow(String msg);
        void SetImage(bool flag);
    }
}
