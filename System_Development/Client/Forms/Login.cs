using ClassLibrary;
using System;
using System.Windows.Forms;

namespace Client.Forms
{
    public partial class Login : Form
    {
        public event EventHandler<MyEventArgs> LoginButton;

        public Login()
        {
            InitializeComponent();
            passwordBox.PasswordChar = '*';
        }

        private void loginButton_Click(object sender, EventArgs e)
        {
            var obj = $"{usernameBox.Text};{Hasher.GenerateHash(passwordBox.Text)}";
            OnLoginButton(obj);
        }

        protected virtual void OnLoginButton(object obj)
        {
            LoginButton?.Invoke(this, new MyEventArgs { MyObject = obj });
        }
    }
}