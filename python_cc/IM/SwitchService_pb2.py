# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: IM.SwitchService.proto

import sys
_b=sys.version_info[0]<3 and (lambda x:x) or (lambda x:x.encode('latin1'))
from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from google.protobuf import reflection as _reflection
from google.protobuf import symbol_database as _symbol_database
from google.protobuf import descriptor_pb2
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()




DESCRIPTOR = _descriptor.FileDescriptor(
  name='IM.SwitchService.proto',
  package='IM.SwitchService',
  serialized_pb=_b('\n\x16IM.SwitchService.proto\x12\x10IM.SwitchService\"M\n\x0bIMP2PCmdMsg\x12\x14\n\x0c\x66rom_user_id\x18\x01 \x02(\r\x12\x12\n\nto_user_id\x18\x02 \x02(\r\x12\x14\n\x0c\x63md_msg_data\x18\x03 \x02(\tB\x1c\n\x18\x63om.sunlands.im.protobufH\x03')
)
_sym_db.RegisterFileDescriptor(DESCRIPTOR)




_IMP2PCMDMSG = _descriptor.Descriptor(
  name='IMP2PCmdMsg',
  full_name='IM.SwitchService.IMP2PCmdMsg',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='from_user_id', full_name='IM.SwitchService.IMP2PCmdMsg.from_user_id', index=0,
      number=1, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='to_user_id', full_name='IM.SwitchService.IMP2PCmdMsg.to_user_id', index=1,
      number=2, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='cmd_msg_data', full_name='IM.SwitchService.IMP2PCmdMsg.cmd_msg_data', index=2,
      number=3, type=9, cpp_type=9, label=2,
      has_default_value=False, default_value=_b("").decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=44,
  serialized_end=121,
)

DESCRIPTOR.message_types_by_name['IMP2PCmdMsg'] = _IMP2PCMDMSG

IMP2PCmdMsg = _reflection.GeneratedProtocolMessageType('IMP2PCmdMsg', (_message.Message,), dict(
  DESCRIPTOR = _IMP2PCMDMSG,
  __module__ = 'IM.SwitchService_pb2'
  # @@protoc_insertion_point(class_scope:IM.SwitchService.IMP2PCmdMsg)
  ))
_sym_db.RegisterMessage(IMP2PCmdMsg)


DESCRIPTOR.has_options = True
DESCRIPTOR._options = _descriptor._ParseOptions(descriptor_pb2.FileOptions(), _b('\n\030com.sunlands.im.protobufH\003'))
# @@protoc_insertion_point(module_scope)
