namespace DarkAge_DatabaseEditor
{
	partial class NameInputDialog
	{
		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.IContainer components = null;

		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		/// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
		protected override void Dispose(bool disposing)
		{
			if (disposing && (components != null))
			{
				components.Dispose();
			}
			base.Dispose(disposing);
		}

		#region Windows Form Designer generated code

		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
			this.NameInputDialogLabel = new System.Windows.Forms.Label();
			this.NameInputDialogTextBox = new System.Windows.Forms.TextBox();
			this.NameInputDialogCancel = new System.Windows.Forms.Button();
			this.NameInputDialogOK = new System.Windows.Forms.Button();
			this.SuspendLayout();
			// 
			// NameInputDialogLabel
			// 
			this.NameInputDialogLabel.AutoSize = true;
			this.NameInputDialogLabel.Location = new System.Drawing.Point(110, 9);
			this.NameInputDialogLabel.Name = "NameInputDialogLabel";
			this.NameInputDialogLabel.Size = new System.Drawing.Size(70, 12);
			this.NameInputDialogLabel.TabIndex = 0;
			this.NameInputDialogLabel.Text = "Input Name";
			// 
			// NameInputDialogTextBox
			// 
			this.NameInputDialogTextBox.Location = new System.Drawing.Point(12, 28);
			this.NameInputDialogTextBox.Name = "NameInputDialogTextBox";
			this.NameInputDialogTextBox.Size = new System.Drawing.Size(270, 21);
			this.NameInputDialogTextBox.TabIndex = 1;
			// 
			// NameInputDialogCancel
			// 
			this.NameInputDialogCancel.DialogResult = System.Windows.Forms.DialogResult.Cancel;
			this.NameInputDialogCancel.Location = new System.Drawing.Point(50, 58);
			this.NameInputDialogCancel.Name = "NameInputDialogCancel";
			this.NameInputDialogCancel.Size = new System.Drawing.Size(75, 23);
			this.NameInputDialogCancel.TabIndex = 2;
			this.NameInputDialogCancel.Text = "Cancel";
			this.NameInputDialogCancel.UseVisualStyleBackColor = true;
			this.NameInputDialogCancel.Click += new System.EventHandler(this.NameInputDialogCancel_Click);
			// 
			// NameInputDialogOK
			// 
			this.NameInputDialogOK.Location = new System.Drawing.Point(168, 58);
			this.NameInputDialogOK.Name = "NameInputDialogOK";
			this.NameInputDialogOK.Size = new System.Drawing.Size(75, 23);
			this.NameInputDialogOK.TabIndex = 3;
			this.NameInputDialogOK.Text = "OK";
			this.NameInputDialogOK.UseVisualStyleBackColor = true;
			this.NameInputDialogOK.Click += new System.EventHandler(this.NameInputDialogOK_Click);
			// 
			// NameInputDialog
			// 
			this.AcceptButton = this.NameInputDialogOK;
			this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 12F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.BackColor = System.Drawing.SystemColors.Control;
			this.CancelButton = this.NameInputDialogCancel;
			this.ClientSize = new System.Drawing.Size(294, 91);
			this.Controls.Add(this.NameInputDialogOK);
			this.Controls.Add(this.NameInputDialogCancel);
			this.Controls.Add(this.NameInputDialogTextBox);
			this.Controls.Add(this.NameInputDialogLabel);
			this.Name = "NameInputDialog";
			this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
			this.Text = "Name Input Dialog";
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.Label NameInputDialogLabel;
		private System.Windows.Forms.TextBox NameInputDialogTextBox;
		private System.Windows.Forms.Button NameInputDialogCancel;
		private System.Windows.Forms.Button NameInputDialogOK;
	}
}