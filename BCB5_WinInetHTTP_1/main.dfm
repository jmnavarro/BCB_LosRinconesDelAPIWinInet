object MainForm: TMainForm
  Left = 177
  Top = 97
  Width = 567
  Height = 422
  Caption = 'Pruebas de HTTP con WinInet'
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
    Width = 57
    Height = 13
    Cursor = crHandPoint
    Hint = 'Haz clic para navegar al artículo completo'
    Caption = 'WinInet (II)'
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
    Caption = 'Síntesis 15'
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
    Top = 86
    Width = 76
    Height = 13
    Caption = 'JM - Junio/2003'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
  end
  object l_jm: TLabel
    Left = 24
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
    Left = 129
    Top = 4
    Width = 425
    Height = 386
    Anchors = [akLeft, akTop, akRight, akBottom]
    Brush.Color = clBtnFace
    Pen.Color = 12164479
  end
  object l_rincones: TLabel
    Left = 6
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
    Left = 131
    Top = 5
    Width = 419
    Height = 381
    Anchors = [akLeft, akTop, akRight, akBottom]
    BevelOuter = bvNone
    TabOrder = 0
    object TLabel
      Left = 16
      Top = 15
      Width = 23
      Height = 13
      Caption = 'URL:'
    end
    object Label1: TLabel
      Left = 9
      Top = 158
      Width = 52
      Height = 13
      Caption = 'Resultado:'
    end
    object TShape
      Left = 66
      Top = 165
      Width = 346
      Height = 1
      Anchors = [akLeft, akTop, akRight]
      Brush.Color = clBtnFace
      Pen.Color = 12164479
    end
    object TShape
      Left = 49
      Top = 21
      Width = 360
      Height = 1
      Anchors = [akLeft, akTop, akRight]
      Brush.Color = clBtnFace
      Pen.Color = 12164479
    end
    object TLabel
      Left = 37
      Top = 40
      Width = 32
      Height = 13
      Caption = 'http://'
    end
    object Label2: TLabel
      Left = 9
      Top = 314
      Width = 21
      Height = 13
      Caption = 'Log:'
    end
    object TShape
      Left = 33
      Top = 321
      Width = 380
      Height = 1
      Anchors = [akLeft, akTop, akRight]
      Brush.Color = clBtnFace
      Pen.Color = 12164479
    end
    object TLabel
      Left = 16
      Top = 87
      Width = 46
      Height = 13
      Caption = 'Acciones:'
    end
    object TShape
      Left = 65
      Top = 94
      Width = 345
      Height = 1
      Anchors = [akLeft, akTop, akRight]
      Brush.Color = clBtnFace
      Pen.Color = 12164479
    end
    object Label3: TLabel
      Left = 273
      Top = 113
      Width = 8
      Height = 16
      Caption = '>'
      Font.Charset = ANSI_CHARSET
      Font.Color = 12164479
      Font.Height = -13
      Font.Name = 'Courier New'
      Font.Style = []
      ParentFont = False
    end
    object TShape
      Left = 207
      Top = 121
      Width = 71
      Height = 1
      Brush.Color = clBtnFace
      Pen.Color = 12164479
    end
    object p_resultado: TPanel
      Left = 9
      Top = 179
      Width = 403
      Height = 117
      Anchors = [akLeft, akTop, akRight]
      BevelOuter = bvNone
      TabOrder = 0
      object p_tab: TPanel
        Left = 0
        Top = 0
        Width = 403
        Height = 117
        Align = alClient
        BevelOuter = bvNone
        Caption = 'p_tab'
        TabOrder = 0
        object pc_resultado: TPageControl
          Left = 1
          Top = 0
          Width = 403
          Height = 118
          ActivePage = ts_archivo
          Anchors = [akLeft, akTop, akRight, akBottom]
          TabOrder = 0
          OnChange = pc_resultadoChange
          object ts_archivo: TTabSheet
            Caption = 'Archivo'
            object TLabel
              Left = 5
              Top = 13
              Width = 60
              Height = 13
              Caption = 'Localización:'
            end
            object TLabel
              Left = 18
              Top = 39
              Width = 47
              Height = 13
              Caption = 'Abrir con:'
            end
            object b_abrir: TButton
              Left = 320
              Top = 65
              Width = 69
              Height = 20
              Anchors = [akRight, akBottom]
              Caption = 'Abrir'
              Enabled = False
              TabOrder = 0
              OnClick = b_abrirClick
            end
            object e_localizacion: TEdit
              Left = 70
              Top = 9
              Width = 319
              Height = 21
              Anchors = [akLeft, akTop, akRight]
              Color = clBtnFace
              TabOrder = 1
            end
            object e_asociado: TEdit
              Left = 70
              Top = 35
              Width = 319
              Height = 21
              Anchors = [akLeft, akTop, akRight]
              Color = clBtnFace
              TabOrder = 2
            end
          end
          object ts_vista: TTabSheet
            Caption = 'Vista'
            ImageIndex = 1
            object m_vista: TMemo
              Left = 1
              Top = 2
              Width = 392
              Height = 86
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
            end
          end
        end
      end
    end
    object cb_url: TComboBox
      Left = 71
      Top = 37
      Width = 338
      Height = 21
      Anchors = [akLeft, akTop, akRight]
      ItemHeight = 13
      TabOrder = 1
      Text = 'www.grupoalbor.com/index.html'
      Items.Strings = (
        'www.grupoalbor.com/index.html'
        'www.grupoalbor.com/figuras/banneralbor.gif'
        'www.grupoalbor.com/Articulos/CursoOracle/CursoOracle.pdf'
        'users.servicios.retecal.es/sapivi/prog/cpp/BCB5_WinInetIntro.zip')
    end
    object lb_log: TListBox
      Left = 9
      Top = 333
      Width = 406
      Height = 43
      Anchors = [akLeft, akTop, akRight, akBottom]
      ItemHeight = 13
      TabOrder = 2
    end
    object b_opciones: TButton
      Left = 64
      Top = 109
      Width = 137
      Height = 24
      Caption = 'Opciones de descarga...'
      TabOrder = 3
      OnClick = b_opcionesClick
    end
    object b_descargar: TButton
      Left = 288
      Top = 109
      Width = 97
      Height = 24
      Caption = '¡Descargar!'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 4
      OnClick = b_descargarClick
    end
  end
end
