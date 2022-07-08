package atm;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Arrays;

import atm.MyExceptions.*;

public class ChangePassword extends JFrame implements ActionListener {
    private JLabel oldPasswordLJLabel, newPasswordJLabel, confirmPasswordJLabel;
    private JPasswordField oldPassword, newPassword, confirmPassword;
    private JButton cancel, confirm, reset;

    public ChangePassword() throws Exception {
        super("改密界面");
        this.setBounds(500, 500, 350, 300);
        this.setLocationRelativeTo(null);
        this.setDefaultCloseOperation(JFrame.DO_NOTHING_ON_CLOSE);
        this.setLayout(null);

        if (Test.currentAccount == null) {
            throw new CardIDException("还没有登录任何账户");
        } else {
            Test.menu.hideScreen();
        }

        oldPasswordLJLabel = new JLabel("原密码:");
        oldPasswordLJLabel.setSize(80, 30);
        oldPasswordLJLabel.setLocation(80, 30);
        oldPasswordLJLabel.setFont(new Font("宋体", Font.BOLD, 16));
        this.add(oldPasswordLJLabel);

        oldPassword = new JPasswordField(20);
        oldPassword.setSize(120, 30);
        oldPassword.setLocation(170, 30);
        this.add(oldPassword);

        newPasswordJLabel = new JLabel("新密码:");
        newPasswordJLabel.setSize(80, 30);
        newPasswordJLabel.setLocation(80, 75);
        newPasswordJLabel.setFont(new Font("宋体", Font.BOLD, 16));
        this.add(newPasswordJLabel);

        newPassword = new JPasswordField(20);
        newPassword.setSize(120, 30);
        newPassword.setLocation(170, 75);
        this.add(newPassword);

        confirmPasswordJLabel = new JLabel("再次输入新密码:");
        confirmPasswordJLabel.setSize(130, 30);
        confirmPasswordJLabel.setLocation(30, 130);
        confirmPasswordJLabel.setFont(new Font("宋体", Font.BOLD, 16));
        this.add(confirmPasswordJLabel);

        confirmPassword = new JPasswordField(20);
        confirmPassword.setSize(120, 30);
        confirmPassword.setLocation(170, 130);
        this.add(confirmPassword);

        cancel = new JButton("返回");
        cancel.setSize(80, 40);
        cancel.setLocation(30, 200);
        cancel.addActionListener(this);
        this.add(cancel);

        confirm = new JButton("修改");
        confirm.setSize(80, 40);
        confirm.setLocation(130, 200);
        confirm.addActionListener(this);
        this.add(confirm);

        reset = new JButton("重置");
        reset.setSize(80, 40);
        reset.setLocation(230, 200);
        reset.addActionListener(this);
        this.add(reset);

        this.setVisible(true);
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        if (e.getActionCommand().equals("返回")) {
            this.setVisible(false);
            Test.menu.showScreen();
        }
        if (e.getActionCommand().equals("重置")) {
            oldPassword.setText("");
            newPassword.setText("");
            confirmPassword.setText("");
        }
        if (e.getActionCommand().equals("修改")) {
            if (!String.valueOf(oldPassword.getPassword()).equals(Test.currentAccount.getPassword())) {
                JOptionPane.showMessageDialog(null, "原密码错误", "提示消息", JOptionPane.ERROR_MESSAGE);
                oldPassword.setText("");
                newPassword.setText("");
                confirmPassword.setText("");
                return;
            }
            if (!Arrays.equals(newPassword.getPassword(), confirmPassword.getPassword())) {
                JOptionPane.showMessageDialog(null, "两次输入的密码不一致", "提示消息", JOptionPane.ERROR_MESSAGE);
                newPassword.setText("");
                confirmPassword.setText("");
                return;
            }
            try {
                Test.currentAccount.ChangePassword(String.valueOf(confirmPassword.getPassword()));
            } catch (NoException e0) {
                JOptionPane.showMessageDialog(null, e0.getMessage());
                this.setVisible(false);
                Test.menu.showScreen();
            } catch (PasswordException e1) {
                JOptionPane.showMessageDialog(null, e1.getMessage());
            } catch (Exception e1) {
                e1.printStackTrace();
            }
        }
    }
}
