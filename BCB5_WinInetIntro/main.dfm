object MainForm: TMainForm
  Left = 200
  Top = 104
  Width = 566
  Height = 323
  Caption = 'Pruebas con WinInet - C++ Builder'
  Color = clBtnFace
  Font.Charset = ANSI_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object sh_funcion: TShape
    Left = 4
    Top = 148
    Width = 127
    Height = 26
    Brush.Color = clBtnFace
    Pen.Color = 12164479
  end
  object i_icono: TImage
    Left = 10
    Top = 7
    Width = 32
    Height = 32
    AutoSize = True
  end
  object l_wininet: TLabel
    Left = 55
    Top = 9
    Width = 53
    Height = 13
    Cursor = crHandPoint
    Hint = 'Haz clic para navegar al artículo completo'
    Caption = 'WinInet (I)'
    Font.Charset = ANSI_CHARSET
    Font.Color = clBlue
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    ParentShowHint = False
    ShowHint = True
    OnClick = l_wininetClick
  end
  object l_sintesis: TLabel
    Left = 56
    Top = 25
    Width = 51
    Height = 13
    Cursor = crHandPoint
    Hint = 'Haz clic para navegar al la página de Síntesis'
    Caption = 'Síntesis 14'
    Font.Charset = ANSI_CHARSET
    Font.Color = clTeal
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    ParentShowHint = False
    ShowHint = True
    OnClick = l_sintesisClick
  end
  object TLabel
    Left = 24
    Top = 82
    Width = 72
    Height = 13
    Caption = 'JM - Abril/2003'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
  end
  object l_jm: TLabel
    Left = 24
    Top = 82
    Width = 13
    Height = 13
    Cursor = crHandPoint
    Hint = 'Haz clic aquí para navegar a "La página de JM"'
    Caption = 'JM'
    Color = clBtnFace
    Font.Charset = ANSI_CHARSET
    Font.Color = clBlue
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentColor = False
    ParentFont = False
    ParentShowHint = False
    ShowHint = True
    Transparent = True
    OnClick = l_jmClick
  end
  object TShape
    Left = 129
    Top = 4
    Width = 424
    Height = 287
    Anchors = [akLeft, akTop, akRight, akBottom]
    Brush.Color = clBtnFace
    Pen.Color = 12164479
  end
  object l_url: TLabel
    Left = 12
    Top = 154
    Width = 95
    Height = 13
    Caption = 'Marcado del módem'
    Transparent = True
    OnClick = CambioFunciones
  end
  object l_conexion: TLabel
    Left = 12
    Top = 194
    Width = 89
    Height = 13
    Cursor = crHandPoint
    Caption = 'Gestión de cookies'
    Color = clBtnFace
    Font.Charset = ANSI_CHARSET
    Font.Color = clBlue
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentColor = False
    ParentFont = False
    Transparent = True
    OnClick = CambioFunciones
  end
  object TLabel
    Left = 4
    Top = 120
    Width = 52
    Height = 13
    Caption = 'Funciones:'
  end
  object l_rincones: TLabel
    Left = 6
    Top = 49
    Width = 117
    Height = 26
    Cursor = crHandPoint
    Hint = 
      'Haz clic para navegar a la página de "Los rincones del API Win32' +
      '"'
    Alignment = taCenter
    AutoSize = False
    Caption = 'Los rincones del API Win32'
    Font.Charset = ANSI_CHARSET
    Font.Color = clBlue
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    ParentShowHint = False
    ShowHint = True
    Layout = tlCenter
    WordWrap = True
    OnClick = l_rinconesClick
  end
  object p_funciones: TPanel
    Left = 131
    Top = 5
    Width = 418
    Height = 282
    Anchors = [akLeft, akTop, akRight, akBottom]
    BevelOuter = bvNone
    TabOrder = 0
    object pc_funciones: TPageControl
      Left = -2
      Top = -27
      Width = 422
      Height = 311
      ActivePage = ts_modem
      Anchors = [akLeft, akTop, akRight, akBottom]
      TabOrder = 0
      TabStop = False
      object ts_modem: TTabSheet
        object pc_modem: TPageControl
          Left = 2
          Top = 6
          Width = 413
          Height = 278
          ActivePage = ts_autodial
          Anchors = [akLeft, akTop, akRight, akBottom]
          TabOrder = 0
          object ts_autodial: TTabSheet
            Caption = 'InternetAutodial'
            object TLabel
              Left = 16
              Top = 16
              Width = 109
              Height = 13
              Caption = 'Opciones de conexión:'
            end
            inline AutodialFrame: TEjecutarFrame
              Top = 206
              Width = 405
              Align = alBottom
              inherited p_pie: TPanel
                Width = 405
                inherited l_retorno2: TLabel
                  Width = 43
                end
                inherited l_retorno: TLabel
                  Width = 272
                end
                inherited Bevel1: TBevel
                  Width = 393
                end
                inherited b_ejecutar: TButton
                  Left = 333
                end
              end
            end
            object AutodialFlags: TCheckListBox
              Left = 16
              Top = 36
              Width = 378
              Height = 45
              Anchors = [akLeft, akTop, akRight]
              ItemHeight = 16
              Items.Strings = (
                'INTERNET_AUTODIAL_FORCE_ONLINE'
                'INTERNET_AUTODIAL_FORCE_UNATTENDED')
              Style = lbOwnerDrawFixed
              TabOrder = 1
            end
          end
          object ts_autodialHangup: TTabSheet
            Caption = 'InternetAutodialHangup'
            ImageIndex = 1
            object TLabel
              Left = 0
              Top = 0
              Width = 208
              Height = 16
              Align = alClient
              Alignment = taCenter
              Caption = 'Esta función no tiene parámetros.'
              Font.Charset = ANSI_CHARSET
              Font.Color = clWindowText
              Font.Height = -13
              Font.Name = 'Arial'
              Font.Style = [fsBold, fsItalic]
              ParentFont = False
              Layout = tlCenter
              WordWrap = True
            end
            inline AutodialHangupFrame: TEjecutarFrame
              Top = 206
              Width = 404
              Align = alBottom
              inherited p_pie: TPanel
                Width = 404
                inherited l_retorno2: TLabel
                  Width = 43
                end
                inherited l_retorno: TLabel
                  Width = 271
                end
                inherited Bevel1: TBevel
                  Width = 392
                end
                inherited b_ejecutar: TButton
                  Left = 332
                end
              end
            end
          end
          object ts_dial: TTabSheet
            Caption = 'InternetDial'
            ImageIndex = 2
            object TLabel
              Left = 16
              Top = 16
              Width = 109
              Height = 13
              Caption = 'Opciones de conexión:'
            end
            object TLabel
              Left = 16
              Top = 152
              Width = 120
              Height = 13
              Caption = 'Identicador de conexión:'
            end
            inline DialFrame: TEjecutarFrame
              Top = 206
              Width = 405
              Align = alBottom
              TabOrder = 1
              inherited p_pie: TPanel
                Width = 404
                inherited l_retorno2: TLabel
                  Width = 43
                end
                inherited l_retorno: TLabel
                  Width = 271
                end
                inherited Bevel1: TBevel
                  Width = 392
                end
                inherited b_ejecutar: TButton
                  Left = 332
                end
              end
            end
            object DialFlags: TCheckListBox
              Left = 16
              Top = 36
              Width = 378
              Height = 88
              Anchors = [akLeft, akTop, akRight]
              ItemHeight = 16
              Items.Strings = (
                'INTERNET_AUTODIAL_FORCE_ONLINE'
                'INTERNET_AUTODIAL_FORCE_UNATTENDED'
                'INTERNET_DIAL_FORCE_PROMPT'
                'INTERNET_DIAL_UNATTENDED'
                'INTERNET_DIAL_SHOW_OFFLINE')
              Style = lbOwnerDrawFixed
              TabOrder = 2
            end
            object e_idConn: TEdit
              Left = 16
              Top = 172
              Width = 121
              Height = 20
              TabStop = False
              AutoSelect = False
              AutoSize = False
              Color = clBtnFace
              Enabled = False
              TabOrder = 0
            end
          end
          object ts_hangup: TTabSheet
            Caption = 'InternetHangUp'
            ImageIndex = 3
            object TLabel
              Left = 16
              Top = 16
              Width = 120
              Height = 13
              Caption = 'Identicador de conexión:'
            end
            inline HangupFrame: TEjecutarFrame
              Top = 206
              Width = 404
              Align = alBottom
              inherited p_pie: TPanel
                Width = 404
                inherited l_retorno2: TLabel
                  Width = 43
                end
                inherited l_retorno: TLabel
                  Width = 271
                end
                inherited Bevel1: TBevel
                  Width = 392
                end
                inherited b_ejecutar: TButton
                  Left = 332
                end
              end
            end
            object e_idConn2: TEdit
              Left = 16
              Top = 36
              Width = 121
              Height = 20
              TabStop = False
              AutoSelect = False
              AutoSize = False
              Color = clBtnFace
              Enabled = False
              TabOrder = 1
            end
          end
        end
      end
      object ts_cookies: TTabSheet
        ImageIndex = 1
        object pc_cookies: TPageControl
          Left = 2
          Top = 6
          Width = 413
          Height = 278
          ActivePage = ts_setcookie
          Anchors = [akLeft, akTop, akRight, akBottom]
          TabOrder = 0
          object ts_setcookie: TTabSheet
            Caption = 'InternetSetCookie'
            object TLabel
              Left = 11
              Top = 24
              Width = 68
              Height = 13
              Caption = 'URL asociada:'
            end
            object TLabel
              Left = 11
              Top = 69
              Width = 42
              Height = 13
              Caption = 'Variable:'
            end
            object TLabel
              Left = 11
              Top = 106
              Width = 28
              Height = 13
              Caption = 'Valor:'
            end
            inline SetCookieFrame: TEjecutarFrame
              Top = 206
              Width = 404
              Align = alBottom
              inherited p_pie: TPanel
                Width = 404
                inherited l_retorno2: TLabel
                  Width = 43
                end
                inherited l_retorno: TLabel
                  Width = 271
                end
                inherited Bevel1: TBevel
                  Width = 392
                end
                inherited b_ejecutar: TButton
                  Left = 332
                end
              end
            end
            object e_urlSetCookie: TEdit
              Left = 90
              Top = 20
              Width = 303
              Height = 21
              Anchors = [akLeft, akTop, akRight]
              TabOrder = 1
              Text = 'http://www.servidor.com'
            end
            object e_variable: TEdit
              Left = 88
              Top = 65
              Width = 305
              Height = 21
              Anchors = [akLeft, akTop, akRight]
              TabOrder = 2
              Text = 'nombre_variable'
            end
            object e_valor: TEdit
              Left = 88
              Top = 102
              Width = 305
              Height = 21
              Anchors = [akLeft, akTop, akRight]
              TabOrder = 3
              Text = 'valor_variable'
            end
          end
          object ts_getcookie: TTabSheet
            Caption = 'InternetGetCookie'
            ImageIndex = 1
            object TLabel
              Left = 11
              Top = 24
              Width = 68
              Height = 13
              Caption = 'URL asociada:'
            end
            object TLabel
              Left = 11
              Top = 69
              Width = 90
              Height = 13
              Caption = 'Variables y valores'
            end
            object bv: TBevel
              Left = 112
              Top = 76
              Width = 286
              Height = 12
              Anchors = [akLeft, akTop, akRight]
              Shape = bsTopLine
            end
            inline GetCookieFrame: TEjecutarFrame
              Top = 206
              Width = 404
              Align = alBottom
              inherited p_pie: TPanel
                Width = 404
                inherited l_retorno2: TLabel
                  Width = 43
                end
                inherited l_retorno: TLabel
                  Width = 271
                end
                inherited Bevel1: TBevel
                  Width = 392
                end
                inherited b_ejecutar: TButton
                  Left = 332
                end
              end
            end
            object e_urlGetCookie: TEdit
              Left = 90
              Top = 20
              Width = 303
              Height = 21
              Anchors = [akLeft, akTop, akRight]
              TabOrder = 1
              Text = 'http://www.servidor.com'
            end
            object lb_variables: TListBox
              Left = 11
              Top = 89
              Width = 388
              Height = 115
              Anchors = [akLeft, akTop, akRight, akBottom]
              Color = clBtnFace
              ItemHeight = 13
              TabOrder = 2
              TabWidth = 130
            end
          end
        end
      end
    end
  end
  object p_aux: TPanel
    Left = 127
    Top = 149
    Width = 6
    Height = 24
    BevelOuter = bvNone
    TabOrder = 1
  end
  object ActionList1: TActionList
    Left = 8
    Top = 260
    object InetAutodial: TAction
      Category = 'Modem'
      Caption = 'InetAutodial'
      OnExecute = InetAutodialExecute
    end
    object InetAutodialHangup: TAction
      Category = 'Modem'
      Caption = 'InetAutodialHangup'
      OnExecute = InetAutodialHangupExecute
    end
    object InetDial: TAction
      Category = 'Modem'
      Caption = 'InetDial'
      OnExecute = InetDialExecute
    end
    object InetHangup: TAction
      Category = 'Modem'
      Caption = 'InetHangup'
      OnExecute = InetHangupExecute
    end
    object InetSetCookie: TAction
      Category = 'Cookies'
      Caption = 'InetSetCookie'
      OnExecute = InetSetCookieExecute
    end
    object InetGetCookie: TAction
      Category = 'Cookies'
      Caption = 'InetGetCookie'
      OnExecute = InetGetCookieExecute
    end
  end
end
