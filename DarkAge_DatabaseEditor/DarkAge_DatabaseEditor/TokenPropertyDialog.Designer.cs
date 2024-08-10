namespace DarkAge_DatabaseEditor
{
	partial class TokenPropertyDialog
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
			this.ComboBox = new System.Windows.Forms.ComboBox();
			this.TurnNum = new System.Windows.Forms.NumericUpDown();
			this.Num2 = new System.Windows.Forms.NumericUpDown();
			this.TargetComboBox = new System.Windows.Forms.ComboBox();
			this.Num1 = new System.Windows.Forms.NumericUpDown();
			this.Label = new System.Windows.Forms.Label();
			this.Cancel = new System.Windows.Forms.Button();
			this.OK = new System.Windows.Forms.Button();
			((System.ComponentModel.ISupportInitialize)(this.TurnNum)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.Num2)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.Num1)).BeginInit();
			this.SuspendLayout();
			// 
			// ComboBox
			// 
			this.ComboBox.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
			this.ComboBox.FormattingEnabled = true;
			this.ComboBox.Location = new System.Drawing.Point(116, 12);
			this.ComboBox.Name = "ComboBox";
			this.ComboBox.Size = new System.Drawing.Size(241, 20);
			this.ComboBox.TabIndex = 0;
			// 
			// TurnNum
			// 
			this.TurnNum.Location = new System.Drawing.Point(356, 55);
			this.TurnNum.Maximum = new decimal(new int[] {
            65535,
            0,
            0,
            0});
			this.TurnNum.Name = "TurnNum";
			this.TurnNum.Size = new System.Drawing.Size(102, 21);
			this.TurnNum.TabIndex = 5;
			// 
			// Num2
			// 
			this.Num2.Location = new System.Drawing.Point(120, 55);
			this.Num2.Maximum = new decimal(new int[] {
            32767,
            0,
            0,
            0});
			this.Num2.Minimum = new decimal(new int[] {
            32768,
            0,
            0,
            -2147483648});
			this.Num2.Name = "Num2";
			this.Num2.Size = new System.Drawing.Size(102, 21);
			this.Num2.TabIndex = 3;
			// 
			// TargetComboBox
			// 
			this.TargetComboBox.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
			this.TargetComboBox.FormattingEnabled = true;
			this.TargetComboBox.Items.AddRange(new object[] {
            "Self",
            "All"});
			this.TargetComboBox.Location = new System.Drawing.Point(228, 55);
			this.TargetComboBox.Name = "TargetComboBox";
			this.TargetComboBox.Size = new System.Drawing.Size(122, 20);
			this.TargetComboBox.TabIndex = 4;
			// 
			// Num1
			// 
			this.Num1.Location = new System.Drawing.Point(12, 55);
			this.Num1.Maximum = new decimal(new int[] {
            32767,
            0,
            0,
            0});
			this.Num1.Minimum = new decimal(new int[] {
            32768,
            0,
            0,
            -2147483648});
			this.Num1.Name = "Num1";
			this.Num1.Size = new System.Drawing.Size(102, 21);
			this.Num1.TabIndex = 2;
			// 
			// Label
			// 
			this.Label.AccessibleName = "";
			this.Label.AutoSize = true;
			this.Label.Location = new System.Drawing.Point(36, 40);
			this.Label.Name = "Label";
			this.Label.Size = new System.Drawing.Size(389, 12);
			this.Label.TabIndex = 1;
			this.Label.Text = "고정수치                백분율                    적용대상                  지속턴";
			// 
			// Cancel
			// 
			this.Cancel.DialogResult = System.Windows.Forms.DialogResult.Cancel;
			this.Cancel.Location = new System.Drawing.Point(99, 88);
			this.Cancel.Name = "Cancel";
			this.Cancel.Size = new System.Drawing.Size(106, 23);
			this.Cancel.TabIndex = 6;
			this.Cancel.Text = "Cancel";
			this.Cancel.UseVisualStyleBackColor = true;
			this.Cancel.Click += new System.EventHandler(this.Cancel_Click);
			// 
			// OK
			// 
			this.OK.DialogResult = System.Windows.Forms.DialogResult.OK;
			this.OK.Location = new System.Drawing.Point(270, 88);
			this.OK.Name = "OK";
			this.OK.Size = new System.Drawing.Size(106, 23);
			this.OK.TabIndex = 7;
			this.OK.Text = "OK";
			this.OK.UseVisualStyleBackColor = true;
			this.OK.Click += new System.EventHandler(this.OK_Click);
			// 
			// TokenPropertyDialog
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 12F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(472, 123);
			this.Controls.Add(this.OK);
			this.Controls.Add(this.Cancel);
			this.Controls.Add(this.Label);
			this.Controls.Add(this.TurnNum);
			this.Controls.Add(this.Num2);
			this.Controls.Add(this.TargetComboBox);
			this.Controls.Add(this.Num1);
			this.Controls.Add(this.ComboBox);
			this.Name = "TokenPropertyDialog";
			this.Text = "TokenPropertyDialog";
			((System.ComponentModel.ISupportInitialize)(this.TurnNum)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.Num2)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.Num1)).EndInit();
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.ComboBox ComboBox;
		private System.Windows.Forms.NumericUpDown TurnNum;
		private System.Windows.Forms.NumericUpDown Num2;
		private System.Windows.Forms.ComboBox TargetComboBox;
		private System.Windows.Forms.NumericUpDown Num1;
		private System.Windows.Forms.Label Label;
		private System.Windows.Forms.Button Cancel;
		private System.Windows.Forms.Button OK;
	}
}