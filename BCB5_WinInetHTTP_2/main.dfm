object MainForm: TMainForm
  Left = 197
  Top = 131
  Width = 566
  Height = 354
  Caption = 'Pruebas de HTTP con WinInet - C++ Builder'
  Color = clBtnFace
  Font.Charset = ANSI_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  PixelsPerInch = 96
  TextHeight = 13
  object i_icono: TImage
    Left = 4
    Top = 7
    Width = 32
    Height = 32
    AutoSize = True
  end
  object l_wininet: TLabel
    Left = 42
    Top = 9
    Width = 94
    Height = 13
    Cursor = crHandPoint
    Hint = 'Haz clic para navegar al artículo completo'
    Caption = 'WinInet y HTTP (II)'
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
    Left = 59
    Top = 25
    Width = 51
    Height = 13
    Cursor = crHandPoint
    Hint = 'Haz clic para navegar al la página de Síntesis'
    Caption = 'Síntesis 16'
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
    Left = 27
    Top = 86
    Width = 85
    Height = 13
    Caption = 'JM - Agosto/2003'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
  end
  object l_jm: TLabel
    Left = 27
    Top = 86
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
  object s_borde: TShape
    Left = 140
    Top = 4
    Width = 413
    Height = 318
    Anchors = [akLeft, akTop, akRight, akBottom]
    Brush.Color = clBtnFace
    Pen.Color = 12164479
  end
  object l_rincones: TLabel
    Left = 9
    Top = 53
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
    Left = 141
    Top = 5
    Width = 408
    Height = 313
    Anchors = [akLeft, akTop, akRight, akBottom]
    BevelOuter = bvNone
    TabOrder = 0
    object TLabel
      Left = 16
      Top = 8
      Width = 28
      Height = 13
      Caption = 'URLs:'
    end
    object Label1: TLabel
      Left = 16
      Top = 182
      Width = 57
      Height = 13
      Caption = 'Resultados:'
    end
    object Label2: TLabel
      Left = 16
      Top = 119
      Width = 68
      Height = 13
      Caption = 'Descargar en:'
    end
    object Bevel1: TBevel
      Left = 48
      Top = 15
      Width = 355
      Height = 9
      Anchors = [akLeft, akTop, akRight]
      Shape = bsTopLine
    end
    object Bevel2: TBevel
      Left = 77
      Top = 189
      Width = 326
      Height = 9
      Anchors = [akLeft, akTop, akRight]
      Shape = bsTopLine
    end
    object Panel1: TPanel
      Left = 88
      Top = 115
      Width = 315
      Height = 21
      Anchors = [akLeft, akTop, akRight]
      BevelOuter = bvNone
      BorderStyle = bsSingle
      Color = clWindow
      TabOrder = 5
      object Image1: TImage
        Left = 297
        Top = 2
        Width = 16
        Height = 14
        Cursor = crHandPoint
        Hint = 'Haz clic para examinar las carpetas'
        Anchors = [akTop, akRight]
        AutoSize = True
        ParentShowHint = False
        Picture.Data = {
          07544269746D6170D6020000424DD60200000000000036000000280000001000
          00000E0000000100180000000000A0020000120B0000120B0000000000000000
          0000EEEEEF9D6967998180B4B4B6D4D7DAEDEFF0FDFDFDFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFD5BFC0BF5D3FC76134B75D3AAD64
          47A56556987674A5A4A6C5CBCEE3E6E8FCFDFDFDFDFDFFFFFFFFFFFFFFFFFFFF
          FFFFCEA7A5C16D55D06E40D46F3CD36C39D06736C96134B45535A157419A6D5F
          A7877FB7ABACD5D6D8F9FAFBFFFFFFFFFFFFCA9A97D58C74CC7755D57C50D276
          49D27345D1703FD36E3BD46E3BD26736CA6434BE5B33A5543EE7E2E2FFFFFFFF
          FFFFCA9B99DE9D85DA9377DA916DD98D66D8875FD68057D17244CF6B3BCF6D3C
          D16E3DD26D3CC46436D8BFBAFFFFFFFFFFFFC19695E1A18AE1A38BE1A588E0A1
          81DE9B7ADD9572DB8E69D78259D17143CF6B3ACF6A39C26638BC7964F8F3F3FF
          FFFFB3807CE7B19BE0A690DDA793ECC0A9E7B59CE5AE93E3A78BE1A283DE9978
          D98B65D47B50C1673BC67248D2AEA6FFFFFFB4726CEFC2AEE9B7A2D09586E6C0
          B0EBC5B4EEC8B5ECC1ABE8B79FE5B196E4AC90E1A386D29173D5926DCC9684FD
          FCFCB8726AF5D2C0F4CEBAE7B7A3CE8E7FE4B39FE2B2A1DFAD9BEFCDBCEFCCBA
          ECC4B0EABCA7E1B5A0E4BDA7D6A28EE5D2D1BB7871F8DDCDF5D5C3F4CFBBF4CB
          B5EEBEA8E9B19ADFA087D09384EFD4C8EFD1C4EFD0C1EAC8B9E9C9BAF1D2BFD9
          B8B1BF8078FDE7D9F7DCCDF5D5C4F3CEBCF1C9B5F2C6B0EFBFA7E5AC94DC9E88
          DEA089DFA08AA97974E2CCC5E8CEC5C59B96B77670FBE6D8FCE8DAF8DED0F7D9
          CAF6D6C3E8BAA7E1AE9BE9B49EEEBAA2F0BA9FE0957A8A605EF4F4F5FFFFFFF8
          F5F5DBC4C4E2BFB5F8E1D3FDE9DCFBE2D3DDB4A7C0928FD4ACA9D5B6B0CB948D
          CE988ED19588B39C9CFCFCFCFFFFFFFFFFFFFEFEFED2B2B2B57976BE7F78C78D
          84C9BAB9FDFDFDFFFFFFFFFFFFFFFFFFFFFFFFFEFCFCFDFDFDFFFFFFFFFFFFFF
          FFFF}
        ShowHint = True
        OnClick = Image1Click
      end
    end
    object p_resultado: TPanel
      Left = 16
      Top = 203
      Width = 388
      Height = 106
      Anchors = [akLeft, akTop, akRight, akBottom]
      BevelOuter = bvNone
      TabOrder = 0
      object Splitter1: TSplitter
        Left = 153
        Top = 0
        Width = 3
        Height = 106
        Cursor = crHSplit
      end
      object lb_resultado: TListBox
        Left = 0
        Top = 0
        Width = 153
        Height = 106
        Align = alLeft
        ItemHeight = 13
        TabOrder = 0
        OnClick = lb_resultadoClick
      end
      object p_tab: TPanel
        Left = 156
        Top = 0
        Width = 232
        Height = 106
        Align = alClient
        BevelOuter = bvNone
        Caption = 'p_tab'
        TabOrder = 1
        object pc_resultado: TPageControl
          Left = 1
          Top = 0
          Width = 232
          Height = 107
          ActivePage = ts_archivo
          Anchors = [akLeft, akTop, akRight, akBottom]
          TabOrder = 0
          OnChange = pc_resultadoChange
          object ts_archivo: TTabSheet
            Caption = 'Archivo'
            object TLabel
              Left = 6
              Top = 5
              Width = 95
              Height = 13
              Caption = 'Programa asociado:'
            end
            object b_abrir: TButton
              Left = 149
              Top = 54
              Width = 69
              Height = 20
              Anchors = [akRight, akBottom]
              Caption = 'Abrir'
              Enabled = False
              TabOrder = 0
              OnClick = b_abrirClick
            end
            object e_asociado: TEdit
              Left = 6
              Top = 25
              Width = 211
              Height = 21
              Anchors = [akLeft, akTop, akRight]
              Color = clBtnFace
              TabOrder = 1
            end
          end
          object ts_vista: TTabSheet
            Caption = 'Vista'
            ImageIndex = 1
            object m_vista: TMemo
              Left = 1
              Top = 2
              Width = 221
              Height = 75
              Anchors = [akLeft, akTop, akRight, akBottom]
              Color = clBtnFace
              Font.Charset = ANSI_CHARSET
              Font.Color = clWindowText
              Font.Height = -11
              Font.Name = 'Courier New'
              Font.Style = []
              ParentFont = False
              ReadOnly = True
              ScrollBars = ssBoth
              TabOrder = 0
              WordWrap = False
            end
          end
        end
      end
    end
    object lb_url: TListBox
      Left = 16
      Top = 29
      Width = 388
      Height = 56
      Anchors = [akLeft, akTop, akRight]
      IntegralHeight = True
      ItemHeight = 13
      Items.Strings = (
        'http://www.grupoalbor.com/index.html'
        'http://www.lawebdejm.com/index.htm'
        'http://www.lawebdejm.com/index.html'
        'http://www.lawebdejm.com/prog/win32/img/prv/datos.txt')
      TabOrder = 1
      OnClick = lb_urlClick
    end
    object b_anadir: TButton
      Left = 281
      Top = 88
      Width = 59
      Height = 20
      Anchors = [akTop, akRight]
      Caption = 'Añadir'
      TabOrder = 2
      OnClick = b_anadirClick
    end
    object b_eliminar: TButton
      Left = 345
      Top = 88
      Width = 59
      Height = 20
      Anchors = [akTop, akRight]
      Caption = 'Eliminar'
      TabOrder = 3
      OnClick = b_eliminarClick
    end
    object e_carpeta: TEdit
      Left = 91
      Top = 118
      Width = 288
      Height = 16
      Anchors = [akLeft, akTop, akRight]
      BorderStyle = bsNone
      TabOrder = 4
    end
    object b_descargar: TButton
      Left = 16
      Top = 149
      Width = 121
      Height = 22
      Caption = 'Comenzar descarga'
      TabOrder = 6
      OnClick = b_descargarClick
    end
    object progreso: TProgressBar
      Left = 149
      Top = 152
      Width = 252
      Height = 16
      Anchors = [akLeft, akTop, akRight]
      Min = 0
      Max = 100
      Smooth = True
      TabOrder = 7
    end
  end
end
